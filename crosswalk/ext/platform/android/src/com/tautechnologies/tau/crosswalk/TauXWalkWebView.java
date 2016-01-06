package com.tautechnologies.tau.crosswalk;

import com.tautechnologies.tau.crosswalk.TauXWResourceClient;
import com.tautechnologies.tau.crosswalk.TauXWUIClient;

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

import com.rhomobile.rhodes.util.PerformOnUiThread;

import android.net.Uri;




public class TauXWalkWebView implements IRhoWebView {
    private static final String TAG = XWalkView.class.getSimpleName(); 

    private XWalkView mWebView;
    private XWalkUIClient mUIClient;
    private XWalkResourceClient mResourceClient;
    private IRhoConfig mConfig;
    private ViewGroup mContainerView;
    private TextZoom mTextZoom;

    public TauXWalkWebView(Context context) {

        Logger.I(TAG, ">>>>> TauXWalkWebView ctor");

        mWebView = new XWalkView(context);
        mUIClient = new TauXWUIClient(mWebView);
        mResourceClient = new TauXWResourceClient(mWebView);
    }
    
    @Override
    public void setWebClient() {

        Logger.I(TAG, ">>>>> TauXWalkWebView setWebClient");

        PerformOnUiThread.exec(new Runnable() {
            @Override
            public void run() {
                Logger.I(TAG, "Setting TauXWalkUIClient and TauXWalkResourceClient");
                mWebView.setUIClient(mUIClient);
                mWebView.setResourceClient(mResourceClient);
            }
        });
    }

    private void applyWebSettings() {
        Logger.I(TAG, "applyWebSettings");
/*
        double z = getConfig().getDouble(WebViewConfig.PAGE_ZOOM);
        mWebView.setInitialScale((int)(z * 100));
        mWebView.setVerticalScrollBarEnabled(true);
        mWebView.setHorizontalScrollBarEnabled(true);
        mWebView.setVerticalScrollbarOverlay(true);
        mWebView.setHorizontalScrollbarOverlay(true);
        mWebView.setFocusableInTouchMode(true);

        IWebSettingsProvider provider = OsVersionManager.getFeature(IWebSettingsProvider.class);
        provider.fillSettings(mWebView.getSettings(), mConfig);
*/
        RhodesActivity.safeGetInstance().notifyUiCreated();
    }
    
    @Override
    public void setConfig(IRhoConfig config) {
        Logger.I(TAG, ">>>>> TauXWalkWebView setConfig");
        mConfig = config;
        applyWebSettings();
    }
    
    public IRhoConfig getConfig() {
        Logger.I(TAG, ">>>>> TauXWalkWebView getConfig");
        return mConfig;
    }

    @Override
    public View getView() {
        Logger.I(TAG, ">>>>> TauXWalkWebView getView");
        return mWebView;
    }

    @Override
    public void setContainerView(ViewGroup view) {
        Logger.I(TAG, ">>>>> TauXWalkWebView setContainerView");
        mContainerView = view;
    }

    @Override
    public ViewGroup getContainerView() {
        Logger.I(TAG, ">>>>> TauXWalkWebView getContainerView");
        return mContainerView;
    }

    @Override
    public boolean canGoBack() {
        Logger.I(TAG, ">>>>> TauXWalkWebView canGoBack");

        return mWebView.getNavigationHistory().canGoBack();
    }

    @Override
    public void goBack() {
        Logger.I(TAG, ">>>>> TauXWalkWebView goBack");
        mWebView.getNavigationHistory().navigate(XWalkNavigationHistory.Direction.BACKWARD, 1);

    }

    @Override
    public void goForward() {
        Logger.I(TAG, ">>>>> TauXWalkWebView goForward");
        mWebView.getNavigationHistory().navigate(XWalkNavigationHistory.Direction.FORWARD, 1);        

    }

    @Override
    public void reload() {
        Logger.I(TAG, ">>>>> TauXWalkWebView reload");
        mWebView.reload(0);

    }

    @Override
    public void clear() {
        Logger.I(TAG, ">>>>> TauXWalkWebView clear");
        mWebView.clearCache(true);
        mWebView.load("", "");
    }

    @Override
    public String getUrl() {
        Logger.I(TAG, ">>>>> TauXWalkWebView getUrl");

        return mWebView.getUrl();
    }

    @Override
    public void loadUrl(String url) {

        Logger.I(TAG, ">>>>> TauXWalkWebView loadUrl");

        RhoExtManager.getImplementationInstance().onBeforeNavigate(mWebView, url);

        Uri uri = LocalFileProvider.overrideUri(Uri.parse(url));
        if (uri != null) {
            url = Uri.decode(uri.toString());
            Logger.T(TAG, "Override URL: " + url);
        }
        mWebView.load(url,null);

    }

    @Override
    public void loadData(String data, String mime, String encoding) {

        Logger.I(TAG, ">>>>> TauXWalkWebView loadData");
        mWebView.load(null,data);

    }

    @Override
    public void loadDataWithBaseURL(String baseUrl, String data, String mimeType, String encoding, String historyUrl) {
        Logger.I(TAG, ">>>>> TauXWalkWebView loadDataWithBaseURL");
        mWebView.load(null,data);

    }

    @Override
    public void stopLoad() {
        Logger.I(TAG, ">>>>> TauXWalkWebView stopLoad");
        mWebView.stopLoading();        
    }

    @Override
    public void setZoom(double scale) {
        Logger.I(TAG, ">>>>> TauXWalkWebView setZoom");
        mWebView.zoomBy((float)scale);
    }

    @Override
    public void setTextZoom(TextZoom zoom) {
        Logger.I(TAG, ">>>>> TauXWalkWebView setTextZoom");
        mTextZoom = zoom;
    }
    
    @Override
    public TextZoom getTextZoom()
    {
        Logger.I(TAG, ">>>>> TauXWalkWebView getTextZoom");
        return mTextZoom;
    }

    @Override
    public String getEngineId() {
        Logger.I(TAG, ">>>>> TauXWalkWebView getEngineId");
        return "XWALK"+mWebView.getXWalkVersion();
    }

    @Override
    public void onPause() {
        Logger.I(TAG, ">>>>> TauXWalkWebView onPause");
        mWebView.onHide();
    }

    @Override
    public void onResume() {
        Logger.I(TAG, ">>>>> TauXWalkWebView onResume");
        mWebView.onShow();
    }

    @Override
    public void destroy() {
        Logger.I(TAG, ">>>>> TauXWalkWebView destroy");
        mWebView.onDestroy();
    }

    @Override
    public void capture(CaptureFormat format, String path) {
        Logger.I(TAG, ">>>>> TauXWalkWebView capture");
    }
    
    private void saveJpeg(String path) {
        Logger.I(TAG, ">>>>> TauXWalkWebView saveJpeg");
    }

    @Override
    public void addJSInterface(Object obj, String name) {
        Logger.I(TAG, ">>>>> TauXWalkWebView addJSInterface");
        mWebView.addJavascriptInterface(obj,name);
    }
}
