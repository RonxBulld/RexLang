#!/bin/python3
#coding: utf-8

import os, shutil
import platform

########################################
# Function declare.
########################################

def remove_file_if_exist(path):
    if os.path.isfile(path):
        os.remove(path)

########################################
# Config files.
########################################

BuildArgs = {
    'Windows': {
        'Sysroot': os.path.realpath(os.getcwd() + '/../sysroot'),
        'BuildType': 'Release',
        'ConfigTypes': 'Release',
        'ToolchainSpecify': '-A x64 -Thost=x64',
        'ParallelJobs': '',
        'BuildDir': 'build-Windows',
    },
    'Linux': {
        'Sysroot': os.path.realpath(os.getcwd() + '/../sysroot'),
        'BuildType': 'Release',
        'ConfigTypes': 'Release',
        'ToolchainSpecify': '',
        'ParallelJobs': '8',
        'BuildDir': 'build-Linux',
    }
}

########################################
# Select config file and initialize.
########################################

system = platform.system()
if not system in BuildArgs:
    raise "Unknow system - " + system
BuildArgs = BuildArgs[system]
BuildArgs['BuildDir'] = BuildArgs['BuildDir'] + "-" + BuildArgs['BuildType']

rootdir = os.getcwd()

########################################
# ANTLR 4 C++ runtime.
########################################

os.chdir("antlr4-rt-cpp")
# if os.path.exists(BuildArgs['BuildDir']):
#     shutil.rmtree(BuildArgs['BuildDir'], True)
if not os.path.exists(BuildArgs['BuildDir']):
    os.mkdir(BuildArgs['BuildDir'])
os.chdir(BuildArgs['BuildDir'])
os.system(f'cmake -DCMAKE_INSTALL_PREFIX={BuildArgs["Sysroot"]} -DCMAKE_BUILD_TYPE={BuildArgs["BuildType"]} -DCMAKE_CONFIGURATION_TYPES="{BuildArgs["ConfigTypes"]}" -DWITH_STATIC_CRT=Off {BuildArgs["ToolchainSpecify"]} ..')
os.system(f'cmake --build . --parallel {BuildArgs["ParallelJobs"]} --config {BuildArgs["BuildType"]}')
os.system('cmake --install . --strip')
os.chdir(rootdir)
# shutil.rmtree(f'antlr4-rt-cpp/{BuildArgs["BuildDir"]}')
# Remove dynamic libraries.
remove_file_if_exist('../sysroot/lib/libantlr4-runtime.so')
remove_file_if_exist('../sysroot/lib/libantlr4-runtime.so.4.8')
remove_file_if_exist('../sysroot/lib/antlr4-runtime.dll')
shutil.copy2('../sysroot/lib/antlr4-runtime-static.lib', '../sysroot/lib/antlr4-runtime.lib')
