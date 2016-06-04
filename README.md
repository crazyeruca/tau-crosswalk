# tau-crosswalk
Crosswalk extension for RhoMobile Suite.

This repository integrates Crosswalk project into RhoMobile.
It is now a beta so some bugs or lack of functionality is possible.

Usage: modify build.yml of your Rhomobile application as follows:

android:
  extensions:
  - crosswalk

paths:
  extensions:
  - </path/to/tau-crosswalk>
