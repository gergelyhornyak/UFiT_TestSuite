#pragma once

#include <string.h>
#include <gtest/gtest.h>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <chrono>
#include <stdlib.h>
#include <stdio.h>

extern std::string ufit_dir_path;

/*
float step_size = 0.005f; // -dl: step size 
int max_steps = 5000; // -ms: max steps
int num_of_processors = -0; // -np: number of processors
bool periodic_phi = true; // -pp: periodic φ
bool periodic_X = false; // -px: periodic X
bool periodic_Y = false; // -py: periodic Y
bool periodic_Z = false; // -pz: periodic Z
bool normalised_B = true; // -nb: normalised B for Q calc
bool save_fieldline_endpoints = true; // -se: save fieldline endpoints
bool save_fieldlines = true; // -sf: save fieldlines
bool save_squashing_factor = true; // -sq: save squashing factor Q
bool print_resources = false;  // -r
bool check_start_points = false; // -cs
int geometry = 1; // -g:  geometry 
*/


std::string commandAssembler(float step_size,int max_steps,int num_of_processors, 
    bool periodic_phi, bool periodic_X, bool periodic_Y, bool periodic_Z, 
    bool normalised_B, bool save_fieldline_endpoints, bool save_fieldlines,
    bool save_squashing_factor, bool print_resources, bool check_start_points,
    int geometry);
