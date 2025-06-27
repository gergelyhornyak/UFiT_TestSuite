#include "testSuiteHeader.hpp"

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
    int geometry){

    std::string B_file_path = "ufit_dipole.bin"; // -b:  B file path
    std::string input_file_path = "ufitdipole.inp"; // -i:  Input file path
    std::string output_file_path = "ufit_dipole_norm.flf"; // -o:  Output file path

    std::string dl = (step_size != NULL) ? " -dl " + std::to_string(step_size) : " ";
    std::string ms = (max_steps != NULL) ? " -ms " + std::to_string(max_steps) : " ";
    std::string np = (num_of_processors != NULL) ? " -np " + std::to_string(num_of_processors) : " ";
    std::string g = (geometry != NULL) ? " -g " + std::to_string(geometry) : " ";

    std::string pp = (periodic_phi) ? " -pp " : " ";
    std::string se = (save_fieldline_endpoints) ? " -se " : " ";
    std::string sf = (save_fieldlines) ? " -sf " : " ";
    std::string sq = (save_squashing_factor) ? " -sq " : " ";

    std::string b = (B_file_path!="") ? " -b " + B_file_path : " ";
    std::string i = (input_file_path!="") ? " -i " + input_file_path : " ";
    std::string o = (output_file_path!="") ? " -o " + output_file_path : " ";

    //std::string repo_path = "../../target_copy/UFiT && ";
    // "cd " + repo_path + 
    std::string cmd = ufit_dir_path + "Run_UFiT" + dl + ms + np + pp + se + sf + sq + g + b + i + o;
    return cmd;
}