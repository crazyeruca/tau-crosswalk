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

import com.rhomobile.rhodes.util.PerformOnUiThread;

import android.net.Uri;

public class TauXWUIClient extends XWalkUIClient {

    private static final String TAG = TauXWUIClient.class.getSimpleName();

/*
    private class AlertResult implements IRhoExtension.IAlertResult {
        private boolean mPending = false;
        private JsResult mResult;
        public AlertResult(JsResult result) {
            mResult = result;
        }
        @Override
        public void setPending() {
            mPending = true;
        }
        @Override
        public void confirm() {
            mResult.confirm();
        }
        @Override
        public void cancel() {
            mResult.cancel();
        }
        public boolean isPending() {
            return mPending;
        }
    }

    private class PromptResult implements IRhoExtension.IPromptResult {
        private boolean mPending = false;
        private JsPromptResult mResult;
        public PromptResult(JsPromptResult result) {
            mResult = result;
        }
        @Override
        public void setPending() {
            mPending = true;
        }
        @Override
        public void confirm(String message) {
            mResult.confirm(message);
        }
        @Override
        public void cancel() {
            mResult.cancel();
        }
        public boolean isPending() {
            return mPending;
        }
    }
*/    

    public TauXWUIClient( XWalkView view ) {
        super(view);
    }

    @Override
    public boolean onJavascriptModalDialog(
        XWalkView view, 
        XWalkUIClient.JavascriptMessageType type, 
        java.lang.String url, 
        java.lang.String message, 
        java.lang.String defaultValue, 
        XWalkJavascriptResult result) {

        Logger.I(TAG, 
            ">>>>> onJavascriptModalDialog: " + url + 
            " type: " + type.toString() +
            " message: " + message
        );

        result.cancel();

/*
        switch(type) {
        case JAVASCTIPT_ALERT:
        break;

        case JAVASCTIPT_CONFIRM:
        break;

        case JAVASCTIPT_PROMPT:
        break;
        }
*/
        return false;

    }
/*
    private boolean onJsAlert(WebView view, String url, String message, JsResult result) {
        AlertResult alertResult = new AlertResult(result);
        RhoExtManager.getImplementationInstance().onAlert(view, message, alertResult);
        return alertResult.isPending();
    }
    
    private boolean onJsConfirm(WebView view, String url, String message, JsResult result) {
        AlertResult alertResult = new AlertResult(result);
        RhoExtManager.getImplementationInstance().onConfirm(view, message, alertResult);
        return alertResult.isPending();
    }

    private boolean onJsPrompt (WebView view, String url, String message, String defaultValue, final JsPromptResult result) {
        PromptResult promptResult = new PromptResult(result);
        RhoExtManager.getImplementationInstance().onPrompt(view, message, defaultValue, promptResult);
        Logger.D(TAG, "JS Prompt is processing by rhodes: " + promptResult.isPending());
        return promptResult.isPending();
    }
*/

    @Override
    public boolean onConsoleMessage(XWalkView view, String message, int lineNumber, String sourceID, XWalkUIClient.ConsoleMessageType messageType) {
        Logger.I(TAG, message + " -- From line " + lineNumber + " of " + sourceID);
        return true;
    }

    @Override
    public void onPageLoadStarted( XWalkView view, String url ) {
        Logger.I(TAG, ">>>>> onPageLoadStarted: " + url);
        super.onPageLoadStarted(view,url);
    }

    @Override
    public void onPageLoadStopped( XWalkView view, String url, XWalkUIClient.LoadStatus status ) {
        Logger.I(TAG, ">>>>> onPageLoadStopped: " + url + " status: " + status.toString() );        
    }

}
