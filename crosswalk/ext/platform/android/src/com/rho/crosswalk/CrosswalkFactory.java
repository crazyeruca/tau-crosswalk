package com.rho.crosswalk;

import com.rhomobile.rhodes.api.RhoApiFactory;

public class CrosswalkFactory
        extends RhoApiFactory< Crosswalk, CrosswalkSingleton>
        implements ICrosswalkFactory {

    @Override
    protected CrosswalkSingleton createSingleton() {
        return new CrosswalkSingleton(this);
    }

    @Override
    protected Crosswalk createApiObject(String id) {
        return new Crosswalk(id);
    }
}
