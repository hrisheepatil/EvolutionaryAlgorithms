clc;
h = 0;
eval = 100000;
cities = load('TSP1.txt');
%disp(cities);
[m,n] = size(cities);
score = zeros(eval,1);
evaluator = zeros(m,eval);
index = 1:m;
index = reshape(index,[m,1]);
%disp(index);
city_list = [cities index];
%disp(city_list);
dist_master = zeros(m,m);
y = zeros(eval,1);
for i = 1:m
    for j = 1:m
        dist_master(i,j) = sqrt((cities(i,1)-cities(j,1))^2 + (cities(i,2)-cities(j,2))^2);
    end
end
%disp(dist_master);
iter = 1;
pop_shuffle = index(randperm(length(index)));
pop_shuffl = pop_shuffle;
%disp('1st random solution');
%disp(pop_shuffl);
dis = 0;
for i1 = 2:m
    dis = dis + dist_master(pop_shuffle(i1,1), pop_shuffle(i1-1,1)); 
end
%disp('1st distance random');
%disp(dis);
i13 = randi(m);
i14 = randi(m);
pop_shuffle([i13 i14]) = pop_shuffle([i14 i13]);
pop_mutate = pop_shuffle;
dis1 = 0;
%disp('1st mutate');
%disp(pop_mutate);
for i1 = 2:m
    dis1 = dis1 + dist_master(pop_mutate(i1,1), pop_mutate(i1-1,1)); 
end
%disp('dist of 1st mutate')
%disp(dis1);
h = h+1;
sco(h,iter) = dis;
h = h+1;
sco(h, iter) = dis1;
score(iter,1) = min([dis dis1]);
%disp(score);
if score(iter,1) == dis
    pop_shuffle = pop_shuffl;
    %disp('random is better');
else
    pop_shuffle = pop_mutate;
    %disp('mutate is better'); 
end
for iter = 2 : eval    
    pop_parent = pop_shuffle;
    dis1 = 0;
    %fprintf('parent (%d)', iter);
    %disp(pop_parent);
    for i1 = 2:m
        dis1 = dis1 + dist_master(pop_mutate(i1,1), pop_mutate(i1-1,1)); 
    end
    %fprintf('distance of (%d) parent', iter);
    %disp(dis1);
    %disp(pop_parent);
    pop_child = pop_shuffle;    
    dis = 0;
    i13 = randi(m);
    i14 = randi(m);
    pop_child([i13 i14]) = pop_child([i14 i13]);
    %fprintf('child (%d)', iter);
    %disp(pop_child)
    for i1 = 2:m
        dis = dis + dist_master(pop_child(i1,1), pop_child(i1-1,1)); 
    end
    %fprintf('distance of (%d) child', iter);
    %disp(dis);
   
    mindis = max([dis dis1]);
    if mindis > score(iter-1,1)
        score(iter,1) = mindis;
    else
        score(iter,1) = score(iter-1, 1);
    end
    %disp(score);
    if score(iter,1) == dis
        pop_shuffle = pop_child;
        %fprintf('child(%d) is better', iter);
    else
        pop_shuffle = pop_parent;
        %fprintf('parent(%d) is better', iter); 
    end
    disp(iter);
end
%disp(score);
xas = 1:eval;
yas = score;
yas1 = sco;
figure(1);
plot(xas,yas);
figure(2);
scatter(xas,yas,10);

