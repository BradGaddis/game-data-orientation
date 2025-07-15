#include "process_manager.h"

 
void ProcessManager::_bind_methods() {
    ClassDB::bind_method(D_METHOD("register_process", "node" , "is_physics"), &ProcessManager::register_process, DEFVAL(true), DEFVAL(true));
    ClassDB::bind_method(D_METHOD("deregister_process", "node" , "is_physics"), &ProcessManager::deregister_process, DEFVAL(true), DEFVAL(true));
}

Array ProcessManager::_cull_dead_nodes(Array nodes) {
	Array culled;
	for (int i = 0; i < nodes.size(); i++) {
        if (nodes[i].get_validated_object()){
            culled.append(nodes[i]);
        }
    }
	return culled;
    
}

void ProcessManager::_process(double p_delta) {
    if (get_tree()->is_paused()) {
        return;
    }
    non_physics_nodes = _cull_dead_nodes(non_physics_nodes);
    for (int i = 0; i < non_physics_nodes.size(); i++) {
        non_physics_nodes.get(i).call("process", p_delta);
    }
}

void ProcessManager::_physics_process(double p_delta) {
    if (get_tree()->is_paused()) {
        return;
    }
    physics_nodes = _cull_dead_nodes(physics_nodes);
    for (int i = 0; i < physics_nodes.size(); i++) {
        physics_nodes.get(i).call("physics_process", p_delta);
    }
}


void ProcessManager::register_process(Node *node, bool physics = true, bool non_physics = true) {
    if (physics && node->has_method("physics_process")){
        physics_nodes.append(node);
        print_line(node->get_name() , " was registered for physics process");
    }
    if (non_physics && node->has_method("process")){
        non_physics_nodes.append(node);
        print_line(node->get_name() , " was registered for non physics process");
    }
}

void ProcessManager::deregister_process(Node *node, bool physics = true, bool non_physics = true) {
    if (physics && node->has_method("physics_process")){
        physics_nodes.erase(node);
        print_line(node->get_name() , " was registered for physics process");
    }
    if (non_physics && node->has_method("process")){
        non_physics_nodes.erase(node);
        print_line(node->get_name() , " was registered for non physics process");
    }
}

ProcessManager::ProcessManager() {

}
