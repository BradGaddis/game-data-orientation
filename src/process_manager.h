
#pragma once

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/Node.hpp>
#include <godot_cpp/core/print_string.hpp>
#include <godot_cpp/classes/scene_tree.hpp>


using namespace godot;

#include <vector>

class ProcessManager : public Node  {
    GDCLASS(ProcessManager, Node);
    enum game_state { 
        dummy,      
    };

    Array physics_nodes;
    Array non_physics_nodes;

protected:
    static void _bind_methods();

public:
    virtual void _process(double p_delta) override;
    virtual void _physics_process(double p_delta) override;
    Array _cull_dead_nodes(Array nodes);
    void register_process(Node *node, bool physics, bool non_physics);
    void deregister_process(Node *node, bool physics, bool non_physics);
    ProcessManager();
};