function generate_input(varargin)
DEFAULT_K = 2;
DEFAULT_N = 2;
DEFAULT_MAX_COORD = 100;

if nargin > 4
    fprintf(2, 'Uzycie: generate_input [k] [n] [max_coord] [seed]\n');
    return;
end

k = DEFAULT_K;
n = DEFAULT_N;
maxCoord = DEFAULT_MAX_COORD;

if nargin >= 1
    k = str2double(string(varargin{1}));
end
if nargin >= 2
    n = str2double(string(varargin{2}));
end
if nargin >= 3
    maxCoord = str2double(string(varargin{3}));
end

if isnan(k) || isnan(n) || isnan(maxCoord)
    fprintf(2, 'Blad: niepoprawny argument liczbowy.\n');
    return;
end

if k <= 0 || n <= 0 || maxCoord < 0
    fprintf(2, 'Blad: wymagane k > 0, n > 0, max_coord >= 0.\n');
    return;
end

if nargin == 4
    seed = str2double(string(varargin{4}));
    if isnan(seed)
        fprintf(2, 'Blad: niepoprawny seed.\n');
        return;
    end
else
    seed = mod(floor(posixtime(datetime('now')) * 1e6), 2^32);
end

rng(double(seed), 'twister');
houseCount = k * n;

fprintf('%d %d\n', k, n);
for i = 1:n
    fprintf('%d %d\n', randi([0, maxCoord]), randi([0, maxCoord]));
end
for i = 1:houseCount
    fprintf('%d %d\n', randi([0, maxCoord]), randi([0, maxCoord]));
end

fprintf(2, 'params: k=%d n=%d max_coord=%d seed=%u\n', k, n, maxCoord, uint32(seed));
end
