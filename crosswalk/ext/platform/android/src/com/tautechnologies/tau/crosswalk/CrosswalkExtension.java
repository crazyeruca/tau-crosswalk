package com.tautechnologies.tau.crosswalk;

import com.rhomobile.rhodes.extmanager.AbstractRhoExtension;
import com.rhomobile.rhodes.extmanager.IRhoWebView;
import com.rhomobile.rhodes.extmanager.IRhoExtManager;
import android.content.Context;


public class CrosswalkExtension extends AbstractRhoExtension {

    @Override
    public IRhoWebView onCreateWebView(IRhoExtManager extManager, int tabIndex) {
        return new TauXWalkWebView( extManager.getContext() );
    }

}