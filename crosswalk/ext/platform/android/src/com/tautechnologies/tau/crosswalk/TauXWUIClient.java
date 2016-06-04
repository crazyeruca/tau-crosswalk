package com.tautechnologies.tau.crosswalk;

import com.rhomobile.rhodes.extmanager.IRhoWebView;
import com.rhomobile.rhodes.extmanager.IRhoConfig;
import com.rhomobile.rhodes.extmanager.IRhoExtManager;
import com.rhomobile.rhodes.extmanager.RhoExtManager;
import com.rhomobile.rhodes.extmanager.RhoExtManagerImpl;
import com.rhomobile.rhodes.extmanager.IRhoExtension;


import org.xwalk.core.XWalkView;
import org.xwalk.core.XWalkUIClient;
import org.xwalk.core.XWalkUIClient.JavascriptMessageType;
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


    private class ModalResult implements IRhoExtension.IAlertResult,IRhoExtension.IPromptResult {
        private boolean mPending = false;
        private XWalkJavascriptResult mResult;
        public ModalResult(XWalkJavascriptResult result) {
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
        public void confirm(String message) {
            mResult.confirmWithResult(message);
        }
        @Override
        public void cancel() {
            mResult.cancel();
        }
        public boolean isPending() {
            return mPending;
        }
    }

    public TauXWUIClient( XWalkView view ) {
        super(view);
    }

    @Override
    public boolean onJavascriptModalDialog(
        XWalkView view, 
        JavascriptMessageType type, 
        java.lang.String url, 
        java.lang.String message, 
        java.lang.String defaultValue, 
        XWalkJavascriptResult result) {

        Logger.I(TAG, 
            ">>>>> onJavascriptModalDialog: " + url + 
            " type: " + type.toString() +
            " message: " + message
        );

        ModalResult rhoResult = new ModalResult(result);
        RhoExtManagerImpl extMgr = RhoExtManager.getImplementationInstance();

        switch(type) {
        case JAVASCRIPT_ALERT:
            extMgr.onAlert(view, message, rhoResult);
            break;

        case JAVASCRIPT_BEFOREUNLOAD:
        case JAVASCRIPT_CONFIRM:
            extMgr.onConfirm(view, message, rhoResult);
            break;

        case JAVASCRIPT_PROMPT:
            extMgr.onPrompt(view, message, defaultValue, rhoResult);
            break;

        default:
            return false;
        }

        return rhoResult.isPending();

    }

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
