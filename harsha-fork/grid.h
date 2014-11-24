
#include <GL/glut.h>
#include <GL/gl.h>
#include <vector>
#include <list>
#include <iostream>

//eigen lib for conjugate gradient
#include "Eigen/IterativeLinearSolvers"

using namespace std;
using namespace Eigen;

typedef Eigen::Triplet<double> T;

class Grid_Cell;

enum model_t {
	PIC,
	FLIP
};

class Particle{

public:

	Particle(float a_x , float a_y, int a_id );
	~Particle();

	int id;


	float x_pos;
	float y_pos;

	Grid_Cell* in_grid;

	float vel_x;
	float vel_y;

};

class Grid_Cell{

public:
	Grid_Cell(int a_x, int a_y);
	~Grid_Cell();

	int x;	
	int y;

	float vel_x;
	float vel_y;
	//float vel_z;

	float temp_count_x;
	float temp_count_y;

	list<Particle*> contained_particles;

	bool particle_present();  // Indicator of whether a particle is present or not
	void clear_vals();

	float temperature;
	float phi; // implicit surface
	float pressure;

	//float stress_tensor

	bool boundary[5]; // 0th index = true => empty else solid ,rest for boundary  1 =  left , 2 = right , 3 = top , 4 = bottom

};





class Grid{

public:
	//takes timestep and cellsize as arguments
	Grid(float a_t,float a_cell_size, model_t a_m);
	~Grid();
	int w,h;
	float cell_size;
	vector< vector< Grid_Cell* > > cells;
	list <Particle* > particles;
	vector< vector< Grid_Cell* > > prev_cells;	// used for flip

	model_t model;
	float time_step;

	// buoyancy
	float alpha;
	float temperature_air;

	void initialise_grid(int a_w,int a_h);
	void initialise_fluid();


	void advect_particles();

	void project_particles_to_grid();

	void save_grid(); 	// for FLIP


	void add_force();
	void check_boundary_conditions();
	void projection_and_pressure_solve();

	void project_grid_to_particles_PIC();
	void project_grid_to_particles_FLIP();

	void temperature_solver();
	float phi_at(int i, int j);
	void implicit_surface_solver();

	void Exec_Time_Step();
	void Draw();

	//helpers
	int convert_grid_to_array_index(int i,int j);
};
