#include "scc.h";

using namespace std;

stack<int> make_node_stack(vector<vector<int> > edge_vec, set<int> node_set){
    stack<int> node_stack;
    stack<int> sorted_node_stack;
    int target_node;
    node_stack.push(*node_set.begin());
    node_set.erase(node_set.begin());

    while(true){
      if(node_stack.size()!=0){
        int top_node = node_stack.top();
        bool found = false;
        for(int i=0; i<edge_vec[top_node].size();i++){
            set<int>::iterator it = node_set.find(edge_vec[top_node][i]);
            if(it != node_set.end()){
              node_stack.push(*it);
              node_set.erase(it);
              found = true;
              break;
            }
        }
        if(!found){
          sorted_node_stack.push(node_stack.top());
          node_stack.pop();
        }
      }else{
        if(node_set.size()!=0){
          node_stack.push(*node_set.begin());
          node_set.erase(node_set.begin());
        }else{
          break;
        }
      }
    }
    return sorted_node_stack;
}

vector<vector<int> > get_sccs(vector<vector<int> > edge_vec, set<int> node_set){
    stack<int> node_stack = make_node_stack(edge_vec, node_set);
    vector<vector<int> > sccs;
    vector<vector<int> > reversed_edge (edge_vec.size());
    for(int i=0; i<edge_vec.size(); i++){
        for(int j=0; j<edge_vec[i].size(); j++){
            reversed_edge[edge_vec[i][j]].push_back(i);
        }
    }

    stack<int> bfs_stack;
    vector<int> current_scc;

    bfs_stack.push(node_stack.top());
    node_set.erase(node_set.find(node_stack.top()));

    node_stack.pop();

    while(true){
      if(bfs_stack.size() != 0){
        int top_node = bfs_stack.top();
        bool found = false;
        for(int i=0; i<reversed_edge[top_node].size(); i++){
          set<int>::iterator it = node_set.find(reversed_edge[top_node][i]);
          if(it != node_set.end()){
            bfs_stack.push(reversed_edge[top_node][i]);
            node_set.erase(it);
            found = true;
            break;
          }
        }
        if(!found){
          current_scc.push_back(bfs_stack.top());
          bfs_stack.pop();
        }
      }else{
        sccs.push_back(current_scc);
        while(node_stack.size() != 0){
          set<int>::iterator it = node_set.find(node_stack.top());
          if(it != node_set.end()){
            current_scc = *new vector<int>;
            bfs_stack.push(*it);
            node_set.erase(it);
            break;
          }else{
            node_stack.pop();
          }
        }
        if(node_stack.size() == 0){
          break;
        }
      }
    }

    return sccs;
}

bool compare_scc_size(vector<int> scc_i, vector<int> scc_j){return scc_i.size()>scc_j.size();}

vector< vector<int> > exec_scc(string file_name){
  set<int> node_set;

  ifstream infile(file_name);

  vector<int> from_vec;
  vector<int> to_vec;

  int node_count = 0;

  int from, to;

  while (infile >> from >> to){
    from_vec.push_back(from-1);
    to_vec.push_back(to-1);
    if(node_count<to){
      node_count = to;
    }
    if(node_count<from){
      node_count = from;
    }
  }

  vector<vector<int> > edges (node_count);
  vector<int> to_nodes;

  for(int i=0; i<from_vec.size(); i++){
    edges[from_vec[i]].push_back(to_vec[i]);
  }

  for(int i=0; i<node_count; i++){
    node_set.insert(i);
  }

  cout << edges.size() << endl;
  cout << node_set.size() << endl;

  vector<vector<int> > sccs = get_sccs(edges, node_set);
  sort(sccs.begin(), sccs.end(), compare_scc_size);
  return sccs;
}
