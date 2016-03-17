// include basic stuff
#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <cstdlib>
#include <unistd.h>
#include <fstream>
#include <time.h>
#include <algorithm>

using namespace std;

// include headers of all outsourced functions
#include "sph_funcs.h"
#include "integrate.h"
#include "linked_list.h"


int main( int argc, const char* argv[]){

        // parsing input parameters
        cout << argc << endl;
        const char* paramFile;
        if (argc != 2) { // Check the value of argc. If not enough parameters have been passed, inform user and exit.
                cout << "You need to provide a parameter file.\n"; // Inform the user of how to use the program
                exit(0);
        } else {
                cout << "Reading parameter file\n";
                paramFile = argv[1]; // name of file containing simulation parameters
        }

        // read from param file
        ifstream inputFile(paramFile);
        string line;
        vector<string> paramvector;

        while (getline(inputFile, line)) {
                if (line.at(0) != '#') { // read only lines without preceding '#'
                        // trim at whitespaces
                        size_t found_whitespace = line.find_first_of(" ");
                        line.erase(found_whitespace);
                        cout << line << endl;
                        paramvector.push_back(line);
                }
        }

        sim_param_t params = initialize_sim_param_t(paramvector);
        sim_state_t* state = init_particles(&params);


        int **lc =  init_lc(params, state);// linked cell
        int *ll  =  init_ll(params, state);//  linked list

        setup_neighbour_list(&params, state, ll, lc);

        int nFrames = params.nFrames;
        int nStepsFrame = params.nStepsFrame;
        float dt = params.dt;
        int n = state->n;

        // print_neighour_list(state,params,ll,lc);


        ofstream out;
        out.open(params.filename,ios::ate); //write new data always at the end (ate)

        compute_accel(state, &params,ll,lc);
        leapfrog_start(state,dt);
        check_state(state);

        print_neighour_list(state,params,ll,lc);

        for (int frame = 1; frame < nFrames; ++frame) { // main simulation loop
                cout << "Calculating Frame " << frame << " of " << nFrames << "\n";
                for (int i = 0; i < nStepsFrame; ++i) { // frame loop
                        compute_accel(state, &params,ll,lc); // update values for accellerations
                        leapfrog_step(state, dt); // update velocities and positions based on previously calculated accelleration
                        check_state(state);
                        usleep(100);
                }
                write_frame_data(frame,out, n, state->x);
                plot_points(frame);
        }

        free_state(state);

        // Plotting simulation results
        // for (int frame = 1; frame < nFrames; ++frame) {
        //  plot_points(frame);
        //  usleep(25000);
        // }
        char c;
        cin >> c;

        return 0;
}
