/* #include "python_runner.hpp"
#include <iostream>

PythonRunner::PythonRunner(const std::string& script_path, const std::string& script_name) 
{
    Py_Initialize();
    PyRun_SimpleString("import sys");
    std::string sys_path = "sys.path.append('" + script_path + "')";
    PyRun_SimpleString(sys_path.c_str());

    PyRun_SimpleString("import sys; print(sys.path)");
    pName = PyUnicode_DecodeFSDefault(script_name.c_str()); 
    pModule = PyImport_Import(pName);
    Py_DECREF(pName);
}

PythonRunner::~PythonRunner() 
{
    Py_XDECREF(pFunc);
    Py_DECREF(pModule);

    Py_Finalize();
}

void PythonRunner::run()
{
    if (pModule != nullptr) {
        pFunc = PyObject_GetAttrString(pModule, "main");  // Assuming there's a main() function in your script
        
        if (pFunc && PyCallable_Check(pFunc)) {
            PyObject_CallObject(pFunc, nullptr);
        } else {
            if (PyErr_Occurred())
                PyErr_Print();
            std::cerr << "Cannot find function 'main'\n";
            Py_XDECREF(pFunc);
        }
    } else {
        PyErr_Print();
        std::cerr << "Failed to load 'fetch_api_script'\n";
    }
}
 */

#include "python_runner.hpp"
#include <iostream>
#include <Python.h>

PythonRunner::PythonRunner(const std::string& script_path, const std::string& script_name) 
{
    Py_Initialize();
    PyRun_SimpleString("import sys");
    std::string sys_path = "sys.path.append('" + script_path + "')";
    PyRun_SimpleString(sys_path.c_str());

    PyRun_SimpleString("import sys; print('Python sys.path:', sys.path, file=sys.stderr)");
    pName = PyUnicode_DecodeFSDefault(script_name.c_str()); 
    pModule = PyImport_Import(pName);
    if (pModule == nullptr) {
        PyErr_Print();
        std::cerr << "Failed to load '" << script_name << "'\n";
    }
    Py_DECREF(pName);
}

PythonRunner::~PythonRunner() 
{
    Py_XDECREF(pFunc);
    Py_XDECREF(pModule);
    /* if (Py_FinalizeEx() < 0) {
        std::cerr << "Error: Py_FinalizeEx() failed\n";
    } */
    Py_Finalize();
}

void PythonRunner::run()
{
    if (pModule != nullptr) {
        pFunc = PyObject_GetAttrString(pModule, "run_main");
        
        if (pFunc && PyCallable_Check(pFunc)) {
            PyObject* pValue = PyObject_CallObject(pFunc, nullptr);
            if (pValue == nullptr) {
                PyErr_Print();
                std::cerr << "Call to run_main() failed\n";
            } else {
                Py_DECREF(pValue);
            }
        } else {
            if (PyErr_Occurred())
                PyErr_Print();
            std::cerr << "Cannot find function 'run_main'\n";
        }
        Py_XDECREF(pFunc);
    } else {
        std::cerr << "Failed to load 'fetch_api_script'\n";
    }
}