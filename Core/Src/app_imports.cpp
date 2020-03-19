/*
 * app_imports.cpp
 *
 *  Created on: Mar 19, 2020
 *      Author: Vladimir
 */

#include "app_imports.h"
#include "Application.h"

static App::Application application;

void appTaskMain(void)
{
  application.taskMain();
}
