#ifndef PYTHON_RUNNER
#define PYTHON_RUNNER
#include <string>
#include <Python.h>
class PythonRunner
{
public:
    PythonRunner(const std::string& script_path, const std::string& script_name);
    ~PythonRunner();
    void run();
private:
PyObject *pName;
PyObject *pModule;
PyObject *pFunc;

};

#endif // PYTHON_RUNNER