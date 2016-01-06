package com.tautechnologies.tau.crosswalk;

import com.rhomobile.rhodes.extmanager.AbstractRhoListener;
import com.rhomobile.rhodes.extmanager.IRhoExtManager;
import com.rhomobile.rhodes.extmanager.RhoExtManager;
import com.rhomobile.rhodes.extmanager.IRhoListener;

import com.tautechnologies.tau.crosswalk.CrosswalkExtension;

public class RhodesListener extends AbstractRhoListener implements IRhoListener {


    @Override
    public void onCreateApplication(IRhoExtManager extManager) {
        RhoExtManager.getInstance().registerExtension("crosswalk", new CrosswalkExtension() );
    }

}
