package com.tautechnologies.tau.crosswalk;

import com.rhomobile.rhodes.extmanager.IRhoWebView;
import com.rhomobile.rhodes.extmanager.IRhoConfig;
import com.rhomobile.rhodes.extmanager.RhoExtManager;


import org.xwalk.core.XWalkView;
import org.xwalk.core.XWalkUIClient;
import org.xwalk.core.XWalkResourceClient;
import org.xwalk.core.XWalkNavigationHistory;
import org.xwalk.core.XWalkJavascriptResult;

import android.app.Activity;
import android.view.View;
import android.view.ViewGroup;

import android.content.Context;

import com.rhomobile.rhodes.LocalFileProvider;
import com.rhomobile.rhodes.Logger;
import com.rhomobile.rhodes.RhodesActivity;
import com.rhomobile.rhodes.RhodesService;
import com.rhomobile.rhodes.extmanager.IRhoExtension;
import com.rhomobile.rhodes.RhoConf;


import com.rhomobile.rhodes.util.PerformOnUiThread;

import android.net.Uri;

import android.net.http.SslError;
import android.webkit.WebResourceResponse;


public class TauXWResourceClient extends XWalkResourceClient {

    private static final String TAG = TauXWResourceClient.class.getSimpleName();


    public TauXWResourceClient( XWalkView view ) {
        super(view);
    }

    @Override
    public boolean shouldOverrideUrlLoading(XWalkView view, String url) {
        Logger.I(TAG, ">>>>> shouldOverrideUrlLoading: " + url);

        //RhoElements implementation of "history:back"
        if(url.equalsIgnoreCase("history:back")) {
            view.getNavigationHistory().navigate(XWalkNavigationHistory.Direction.BACKWARD, 1);
            return true;
        }

        if (url.contains(".HTM")) 
        {
            url=url.replace(".HTML", ".html");
            url=url.replace(".HTM", ".htm");
            Logger.I(TAG, "Changed to lower case html, url="+ url);
        }

        boolean res = RhodesService.getInstance().handleUrlLoading(url);
        if (!res) {
            Logger.profStart("BROWSER_PAGE");

            RhoExtManager.getImplementationInstance().onBeforeNavigate(view, url);

            Uri localUri = LocalFileProvider.overrideUri(Uri.parse(url));
            if (localUri != null) {
                url = Uri.decode(localUri.toString());
                Logger.T(TAG, "Override URL: " + url);
                view.load(url,null);
                return true;
            }
        }
        return res;            
    }

    @Override
    public WebResourceResponse shouldInterceptLoadRequest( XWalkView view, String url ) {
        Logger.I(TAG, ">>>>> shouldInterceptLoadRequest: " + url);
        return super.shouldInterceptLoadRequest(view, url);
    }

    @Override
    public void onLoadStarted( XWalkView view, String url ) {
        Logger.I(TAG, ">>>>> onLoadStarted: " + url);

        super.onLoadStarted(view, url);

        RhoExtManager.getImplementationInstance().onNavigateStarted(view, url);

                //if (mWebView.getConfig() != null && mWebView.getConfig().getBool(WebViewConfig.ENABLE_PAGE_LOADING_INDICATION))
                //    RhodesActivity.safeGetInstance().getWindow().setFeatureInt(Window.FEATURE_PROGRESS, 0);
                //}
    }

    @Override 
    public void onLoadFinished( XWalkView view, String url ) {
        Logger.I(TAG, ">>>>> onLoadFinished: " + url);


        Logger.profStop("BROWSER_PAGE");

        // Set title
        String title = view.getTitle();
        try {
            RhodesActivity.safeGetInstance().setTitle(title);

                    //if (mWebView.getConfig() != null && mWebView.getConfig().getBool(WebViewConfig.ENABLE_PAGE_LOADING_INDICATION))
                    //    RhodesActivity.safeGetInstance().getWindow().setFeatureInt(Window.FEATURE_PROGRESS, RhodesActivity.MAX_PROGRESS);
        } catch (Throwable ex) {
                    //Do nothing. Just for case if activity has been destroyed in between.
        }

        RhoExtManager.getImplementationInstance().onNavigateComplete(view, url);
        //CookieSyncManager.getInstance().sync();

        super.onLoadFinished(view, url);
    }

    @Override
    public void onProgressChanged( XWalkView view, int progressInPercent ) {
        Logger.I(TAG, ">>>>> onProgressChanged: " + (new Integer(progressInPercent)).toString() );

    }

    @Override 
    public void onReceivedLoadError( 
        XWalkView view, 
        int errorCode,
        String description,
        String failingUrl ) {

        super.onReceivedLoadError(view, errorCode, description, failingUrl);

        Logger.I(TAG, ">>>>> onReceivedLoadError: " + description);


        Logger.profStop("BROWSER_PAGE");

        StringBuilder msg = new StringBuilder(failingUrl != null ? failingUrl : "null");
        msg.append(" failed: ");
        msg.append(errorCode);
        msg.append(" - " + description);
        Logger.E(TAG, msg.toString());

        RhoExtManager.getImplementationInstance().onLoadError(view, IRhoExtension.LoadErrorReason.INTERNAL_ERROR);
    }

    @Override
    public void onReceivedSslError(
        XWalkView view, 
        android.webkit.ValueCallback<Boolean> callback, 
        SslError error) {
        
        if(RhoConf.getBool("no_ssl_verify_peer")) {
            Logger.D(TAG, "Skip SSL error.");
            callback.onReceiveValue(true); 
        } else {
            StringBuilder msg = new StringBuilder();
            msg.append("SSL error - ");
            switch(error.getPrimaryError()) {
            case SslError.SSL_NOTYETVALID:
                msg.append("The certificate is not yet valid: ");
                break;
            case SslError.SSL_EXPIRED:
                msg.append("The certificate has expired: ");
                break;
            case SslError.SSL_IDMISMATCH:
                msg.append("Hostname mismatch: ");
                break;
            case SslError.SSL_UNTRUSTED:
                msg.append("The certificate authority is not trusted: ");
                break;
            }
            msg.append(error.getCertificate().toString());
            Logger.W(TAG, msg.toString());
            callback.onReceiveValue(false); 
        }
    }
}