dim = 0
nParticles = 0
n_cells = {0}
lo = {0.0}
hi = {0.0}
dx = (hi[1] - lo[1])/n_cells[1]

dt = 0.0000
start_time = 0.0
stop_time = 0.0
max_steps = 0

print_int = 20
plot_int = 20

freq_plasma = 0.0
q = 0.0
m = 0.0

verbose = 0
rho_back = 0.0
pos_init = {}
vel_init = {}

vt = 0.0

particle_step = "euler"
fields_step = "euler"


