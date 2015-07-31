% Warming up tic/toc.
tic; toc; tic; toc; tic; toc;
% Specifying number of total repeats.
num_rep = 10;
% Initialization of matrix for results.
times = zeros(1,num_rep);
% Main loop.
for k = 1:num_rep
   times(k) = tictoc_time_experiment();
end
% Choose the lower result.
t = min(times)