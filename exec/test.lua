verbose = 0

dim = 1
nParticles = 1000
n_cells = {100}
lo = {0.0}
hi = {1.0}
dx = (hi[1] - lo[1])/n_cells[1]

dt = 0.0005
start_time = 0.0
stop_time = 1.0
max_steps = 2000


freq_plasma = 1.0
q = -0.1
m = 0.1

verbose = 1
rho_back = -q * nParticles / dx
pos_init = {}
vel_init = {}

vt = 0.0

particle_step = "euler"
fields_step = "euler"

dp = (hi[1] - lo[1])/(nParticles)
for idim = 1, dim do
    L = hi[idim]-lo[idim]
    for i = 1,nParticles do
        pos_nom = lo[idim] + (i-0.5) * dp
        pos_pert = L/nParticles * math.sin(2 * math.pi * pos_nom/L*1)
        pos = pos_nom + pos_pert

        if pos > L then
            pos = pos_init - L
        elseif pos < 0 then
            pos = pos + L
        end

        table.insert(pos_init, {})
        table.insert(vel_init, {})

        pos_init[i][idim] = pos
        vel_init[i][idim] = 2*(math.random()-0.5)*vt


    end
end

