function main(varargin)
INF = 1e18;
EPSILON = 1e-9;

if nargin >= 1
    data = sscanf(fileread(varargin{1}), '%f');
else
    data = fscanf(1, '%f');
end

if numel(data) < 2
    error('Invalid input: expected k and n.');
end

k = data(1);
n = data(2);
idx = 3;

wells = zeros(n, 2);
for i = 1:n
    wells(i, :) = [data(idx), data(idx + 1)];
    idx = idx + 2;
end

h = k * n;
houses = zeros(h, 2);
for j = 1:h
    houses(j, :) = [data(idx), data(idx + 1)];
    idx = idx + 2;
end

s = 1;
firstWell = 2;
firstHouse = 2 + n;
t = 2 + n + h;
V = t;

G = cell(V, 1);
edges = struct('to', {}, 'cap', {}, 'flow', {}, 'rev', {}, 'cost', {});

for i = 1:n
    addEdge(s, firstWell + i - 1, k, 0.0);
end

for i = 1:n
    for j = 1:h
        dx = wells(i, 1) - houses(j, 1);
        dy = wells(i, 2) - houses(j, 2);
        addEdge(firstWell + i - 1, firstHouse + j - 1, 1, sqrt(dx * dx + dy * dy));
    end
end

for j = 1:h
    addEdge(firstHouse + j - 1, t, 1, 0.0);
end

[totalFlow, totalCost] = minCostMaxFlow(s, t, V);

if totalFlow ~= h
    error('Error: could not assign all houses (flow=%d, expected=%d)', totalFlow, h);
end

fprintf('Koszt: %.4f\n', totalCost);

for i = 1:n
    u = firstWell + i - 1;
    line = sprintf('S%d', i);
    for ei = G{u}
        e = edges(ei);
        if e.to >= firstHouse && e.to < firstHouse + h && e.flow == 1
            line = sprintf('%s d%d', line, e.to - firstHouse + 1);
        end
    end
    fprintf('%s\n', line);
end

    function addEdge(u, v, cap, cost)
        idxF = numel(edges) + 1;
        idxR = idxF + 1;
        edges(idxF) = struct('to', v, 'cap', cap, 'flow', 0, 'rev', idxR, 'cost', cost);
        edges(idxR) = struct('to', u, 'cap', 0, 'flow', 0, 'rev', idxF, 'cost', -cost);
        G{u}(end + 1) = idxF;
        G{v}(end + 1) = idxR;
    end

    function [found, dist, prevV, prevE] = spfa(source, sink, vertexCount)
        dist = INF * ones(vertexCount, 1);
        prevV = -ones(vertexCount, 1);
        prevE = -ones(vertexCount, 1);
        inQueue = false(vertexCount, 1);

        queue = zeros(vertexCount * 10, 1);
        head = 1;
        tail = 1;

        dist(source) = 0.0;
        queue(tail) = source;
        tail = tail + 1;
        inQueue(source) = true;

        while head < tail
            u = queue(head);
            head = head + 1;
            inQueue(u) = false;

            for ei = G{u}
                e = edges(ei);
                residual = e.cap - e.flow;
                if residual > 0 && dist(u) + e.cost < dist(e.to) - EPSILON
                    dist(e.to) = dist(u) + e.cost;
                    prevV(e.to) = u;
                    prevE(e.to) = ei;
                    if ~inQueue(e.to)
                        queue(tail) = e.to;
                        tail = tail + 1;
                        inQueue(e.to) = true;
                    end
                end
            end
        end

        found = dist(sink) < INF;
    end

    function [totalFlow, totalCost] = minCostMaxFlow(source, sink, vertexCount)
        totalFlow = 0;
        totalCost = 0.0;

        while true
            [found, ~, prevV, prevE] = spfa(source, sink, vertexCount);
            if ~found
                break;
            end

            addFlow = intmax('int32');
            v = sink;
            while v ~= source
                u = prevV(v);
                e = edges(prevE(v));
                addFlow = min(addFlow, e.cap - e.flow);
                v = u;
            end

            v = sink;
            while v ~= source
                u = prevV(v);
                ei = prevE(v);
                rev = edges(ei).rev;
                edges(ei).flow = edges(ei).flow + addFlow;
                edges(rev).flow = edges(rev).flow - addFlow;
                totalCost = totalCost + addFlow * edges(ei).cost;
                v = u;
            end

            totalFlow = totalFlow + addFlow;
        end
    end
end
