//
//  cmdLineArgs.cpp
//  multiThreadEnergyUsage
//
//  Created by Clifford Campo on 6/5/18.
//  Copyright © 2018 CliffordCampo. All rights reserved.
//

#include "cmdLineArgs.hpp"
CmdLineArgs::CmdLineArgs() {
    //Set up the default values for these parameters that may be overridded by the values obtained from the command line.
    _clDatabaseName = "LocalWeather";
    _results_File = "";
    _clUserID = "cjc";
    _clPW = "";
    _clHostID = "localhost";
    _clPortID = "5436";
    _clSQL = "";
    _debug1 = true;
    _debug2 = false;
    _debug3 = false;
    _useKelvin = false;
}
CmdLineArgs::~CmdLineArgs() {
    ;
}
