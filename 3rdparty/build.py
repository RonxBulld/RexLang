#!/bin/python3
#coding: utf-8

import os, shutil
import platform

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
    },
    'Linux': {
        'Sysroot': os.path.realpath(os.getcwd() + '/../sysroot'),
        'BuildType': 'Release',
        'ConfigTypes': 'Release',
        'ToolchainSpecify': '',
        'ParallelJobs': '8',
    }
}

########################################
# Select config file and initialize.
########################################

system = platform.system()
if not system in BuildArgs:
    raise "Unknow system - " + system
BuildArgs = BuildArgs[system]

rootdir = os.getcwd()

########################################
# ANTLR 4 C++ runtime.
########################################

os.chdir("antlr4-rt-cpp")
if os.path.exists('build'):
    shutil.rmtree("build", True)
os.mkdir("build")
os.chdir("build")
os.system(f'cmake -DCMAKE_INSTALL_PREFIX={BuildArgs["Sysroot"]} -DCMAKE_BUILD_TYPE={BuildArgs["BuildType"]} -DCMAKE_CONFIGURATION_TYPES="{BuildArgs["ConfigTypes"]}" {BuildArgs["ToolchainSpecify"]} ..')
os.system(f'cmake --build . --target antlr4_static --parallel {BuildArgs["ParallelJobs"]} --config {BuildArgs["BuildType"]}')
os.system(f'cmake --build . --target antlr4_shared --parallel {BuildArgs["ParallelJobs"]} --config {BuildArgs["BuildType"]}')
os.system('cmake --install .')
os.chdir(rootdir)
shutil.rmtree('antlr4-rt-cpp/build')
