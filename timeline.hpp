#pragma once
#include <vector>
#include <utility>
#include <algorithm>

struct Edge { int u, v; };

// Each edge is active throughout every time interval where it is stored.
class Timeline {
    int base=1, count;
    std::vector<std::vector<Edge>> buckets;
    template<class State, class Visit>
    void walk(int node, int left, int right, State &state, Visit &visit) {
        if (left>=count) return;
        auto mark=state.mark();
        for (auto e : buckets[node]) state.add(e);
        if (right-left==1) visit(left,state);
        else {
            int middle=(left+right)/2;
            walk(2*node,left,middle,state,visit);
            walk(2*node+1,middle,right,state,visit);
        }
        state.undo(mark);
    }
public:
    explicit Timeline(int n):count(n) {
        while (base<n) base*=2;
        buckets.resize(2*base);
    }
    void insert(int left, int right, Edge e) {
        for (left+=base, right+=base; left<right; left/=2,right/=2) {
            if (left%2) buckets[left++].push_back(e);
            if (right%2) buckets[--right].push_back(e);
        }
    }
    template<class State, class Visit>
    void run(State &state, Visit visit) { walk(1,0,base,state,visit); }
};

// Root sizes are negative. No path compression, so each union is reversible.
class RollbackDSU {
    struct Change { int a,b,oldA,oldB; };
    std::vector<int> parent, parity;
    std::vector<Change> log;
    int conflicts=0;
    bool checkParity;
    std::pair<int,int> find(int u) const {
        int color=0;
        while (parent[u]>=0) { color^=parity[u]; u=parent[u]; }
        return {u,color};
    }
public:
    RollbackDSU(int n,bool bipartite):parent(n+1,-1),parity(n+1),checkParity(bipartite) {}
    auto mark() const { return std::make_pair(log.size(),conflicts); }
    void add(Edge e) {
        auto [a,x]=find(e.u);
        auto [b,y]=find(e.v);
        if (a==b) {
            if (checkParity && x==y) ++conflicts;
            return;
        }
        if (parent[a]>parent[b]) std::swap(a,b);
        log.push_back({a,b,parent[a],parent[b]});
        parent[a]+=parent[b]; parent[b]=a;
        parity[b]=x^y^1;
    }
    void undo(std::pair<std::size_t,int> snapshot) {
        while (log.size()>snapshot.first) {
            auto c=log.back(); log.pop_back();
            parent[c.a]=c.oldA; parent[c.b]=c.oldB;
            parity[c.b]=0;
        }
        conflicts=snapshot.second;
    }
    bool bipartite() const { return conflicts==0; }
    int size(int u) const { return -parent[find(u).first]; }
};
