#include "integrate.h"



void leapfrog_start(sim_state_t* s, double dt){
        const float* a = s->a;
        float*  vh = s->vh;
        float*  v = s->v;
        float*  x = s->x;
        int n = s->n;

        // std::cout << "\n--------------a[i]------------\n";
        // for (int i = 0; i < 2*n; ++i) std::cout << a[i] << " ";
        //
        // std::cout << "\n--------------v[i]------------\n";
        // for (int i = 0; i < 2*n; ++i) std::cout << v[i] << " ";
        //
        // std::cout << "\n--------------vh[i]------------\n";
        // for (int i = 0; i < 2*n; ++i) std::cout << vh[i] << " ";

        for (int i = 0; i < 2*n; ++i) vh[i] = v[i] + a[i] * dt/2;

        // std::cout << "\n--------------vh[i]------------\n";
        // for (int i = 0; i < 2*n; ++i) std::cout << vh[i] << " ";


        for (int i = 0; i < 2*n; ++i) v[i] += a[i] * dt;
        for (int i = 0; i < 2*n; ++i) x[i] += vh[i] * dt;




        //
        // std::cout << "\n--------------position------------\n";
        // for (int i = 0; i < 2*n; ++i) std::cout << x[i] << " ";



        // std::cout << std::endl; std::cout << std::endl;
        reflect_bc(s);
}



void leapfrog_step(sim_state_t* s, double dt){
        const float*  a = s->a;
        float*  vh = s->vh;
        float*  v = s->v;
        float*  x = s->x;
        int n = s->n;
        for (int i = 0; i < 2*n; ++i) vh[i] += a[i] * dt;
        for (int i = 0; i < 2*n; ++i) v[i] = vh[i] + a[i] * dt / 2;
        for (int i = 0; i < 2*n; ++i) x[i] += vh[i] * dt;
        // std::cout << "\n--------------position------------\n";
        // for (int i = 0; i < 2*n; ++i) std::cout << x[i] << " ";
        //
        // std::cout << "\n--------------velocity------------\n";
        // for (int i = 0; i < 2*n; ++i) std::cout << v[i] << " ";

        reflect_bc(s);
}
