/*
 * app_imports.cpp
 *
 *  Created on: Mar 19, 2020
 *      Author: Vladimir
 */

#include "application.h"
#include "app_imports.h"

static App::Application application;

void appTaskMain(void)
{
  application.taskMain();
}
