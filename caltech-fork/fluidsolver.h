#include <utility>

class FluidSolver
{
private:
    int n, size;

    float dt;

    float visc;
    float diff;

    float tmp[];

    float *d, *dOld;
    float *u, *uOld;
    float *v, *vOld;
    float *curl;

    inline void clear(float* arr) { for (int i = 0; i < size; i++) arr[i] = 0; }
    inline int I(int i, int j){ return i + (n + 2) * j; }

    void setBoundary(int b, float* x);
    void advect(int b, float* d, float* d0, float* du, float* dv);
    void diffuse(int b, float* c, float* c0, float diff);
    void swap(float* a, float* b);
    void addSource(float* a, float* b);

public:
    FluidSolver(int n, float dt);
    ~FluidSolver();
    void initFluid(pair<int> locations[], int num_locations);
    void reset();
    void buoyancy(float* fbuoy);
    void step();
    void temperatureSolver();
    void velocitySolver();
    void displaceParticles();
    void implicitSurfaceSolver();
    float computeCurl(int i, int j);
    void vorticityConfinement(float* Fvc_x, float* Fvc_y);
    void project(float* x, float* y, float* p, float* div);
    void linearSolver(int b, float* x, float* x0, float a, float c);
    void densitySolver();
};