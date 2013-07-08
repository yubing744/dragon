#include "dg_script_behaviour.h"

#include <v8.h>
using namespace v8;

DGLog* DGScriptBehaviour::LOG = new DGLog("DGScriptBehaviour");

DGScriptBehaviour::DGScriptBehaviour(void)
{
}


DGScriptBehaviour::~DGScriptBehaviour(void)
{
}


void DGScriptBehaviour::init(DGGameObject* gameObject, DGContext* ctx){

}

void DGScriptBehaviour::update(DGContext* ctx){
     // Create a stack-allocated handle scope.
     HandleScope handle_scope;

     // Create a new context.
     Handle<Context> context = Context::New();

     // Enter the created context for compiling and
     // running the hello world script.
     Context::Scope context_scope(context);

     // Create a string containing the JavaScript source code.
     Local<String> source = String::New("1+1");
     // Compile the source code.
     Handle<Script> script = Script::Compile(source);
     // Run the script to get the result.
     Handle<Value> result = script->Run();
     // Convert the result to an ASCII string and print it.
     String::AsciiValue ascii(result);
	 LOG->info("%s\n", *ascii);
}

void DGScriptBehaviour::draw(DGContext* ctx){

}

void DGScriptBehaviour::destroy(){

}

void DGScriptBehaviour::start(){

}
