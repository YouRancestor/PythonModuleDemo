#include <Python.h>
#include <time.h>
#include <list>
#include <vector>
#include <iostream>

/* Use this file as a template to start implementing a module that
   also declares object types. All occurrences of 'Xxo' should be changed
   to something reasonable for your objects. After that, all other
   occurrences of 'xx' should be changed to something reasonable for your
   module. If your module is named foo your sourcefile should be named
   foomodule.c.

   You will probably want to delete all references to 'x_attr' and add
   your own types of attributes instead.  Maybe you want to name your
   local variables other than 'self'.  If your object type is needed in
   other files, you'll have to create a file "foobarobject.h"; see
   floatobject.h for an example. */

/* Xxo objects */

#include "Python.h"

static PyObject *ErrorObject;

typedef struct {
    PyObject_HEAD
    PyObject            *x_attr;        /* Attributes dictionary */
} XxoObject;

static PyObject *
Xxo_demo(XxoObject *self, PyObject *args);
static void
Xxo_dealloc(XxoObject *self);
static PyObject *
Xxo_getattro(XxoObject *self, PyObject *name);
static int
Xxo_setattr(XxoObject *self, const char *name, PyObject *v);
static PyMethodDef Xxo_methods[] = {
    {"demo",            (PyCFunction)Xxo_demo,  METH_VARARGS,
     PyDoc_STR("demo() -> None")},
    {NULL,              NULL}           /* sentinel */
};



static PyTypeObject Xxo_Type = {
    /* The ob_type field must be initialized in the module init function
         * to be portable to Windows without using C++. */
    PyVarObject_HEAD_INIT(NULL, 0)
    "xxmodule.Xxo",             /*tp_name*/
    sizeof(XxoObject),          /*tp_basicsize*/
    0,                          /*tp_itemsize*/
    /* methods */
    (destructor)Xxo_dealloc,    /*tp_dealloc*/
    0,                          /*tp_print*/
    (getattrfunc)0,             /*tp_getattr*/
    (setattrfunc)Xxo_setattr,   /*tp_setattr*/
    0,                          /*tp_reserved*/
    0,                          /*tp_repr*/
    0,                          /*tp_as_number*/
    0,                          /*tp_as_sequence*/
    0,                          /*tp_as_mapping*/
    0,                          /*tp_hash*/
    0,                          /*tp_call*/
    0,                          /*tp_str*/
    (getattrofunc)Xxo_getattro, /*tp_getattro*/
    0,                          /*tp_setattro*/
    0,                          /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT,         /*tp_flags*/
    0,                          /*tp_doc*/
    0,                          /*tp_traverse*/
    0,                          /*tp_clear*/
    0,                          /*tp_richcompare*/
    0,                          /*tp_weaklistoffset*/
    0,                          /*tp_iter*/
    0,                          /*tp_iternext*/
    Xxo_methods,                /*tp_methods*/
    0,                          /*tp_members*/
    0,                          /*tp_getset*/
    0,                          /*tp_base*/
    0,                          /*tp_dict*/
    0,                          /*tp_descr_get*/
    0,                          /*tp_descr_set*/
    0,                          /*tp_dictoffset*/
    0,                          /*tp_init*/
    0,                          /*tp_alloc*/
    0,                          /*tp_new*/
    0,                          /*tp_free*/
    0,                          /*tp_is_gc*/
};
#define XxoObject_Check(v)      (Py_TYPE(v) == &Xxo_Type)

static XxoObject *
newXxoObject(PyObject *arg)
{
    XxoObject *self;
    self = PyObject_New(XxoObject, &Xxo_Type);
    if (self == NULL)
        return NULL;
    self->x_attr = NULL;
    return self;
}

/* Xxo methods */

static void
Xxo_dealloc(XxoObject *self)
{
    Py_XDECREF(self->x_attr);
    PyObject_Del(self);
}

static PyObject *
Xxo_demo(XxoObject *self, PyObject *args)
{
    if (!PyArg_ParseTuple(args, ":demo"))
        return NULL;
    Py_INCREF(Py_None);
    return Py_None;
}


static PyObject *
Xxo_getattro(XxoObject *self, PyObject *name)
{
    if (self->x_attr != NULL) {
        PyObject *v = PyDict_GetItem(self->x_attr, name);
        if (v != NULL) {
            Py_INCREF(v);
            return v;
        }
    }
    return PyObject_GenericGetAttr((PyObject *)self, name);
}

static int
Xxo_setattr(XxoObject *self, const char *name, PyObject *v)
{
    if (self->x_attr == NULL) {
        self->x_attr = PyDict_New();
        if (self->x_attr == NULL)
            return -1;
    }
    if (v == NULL) {
        int rv = PyDict_DelItemString(self->x_attr, name);
        if (rv < 0)
            PyErr_SetString(PyExc_AttributeError,
                            "delete non-existing Xxo attribute");
        return rv;
    }
    else
        return PyDict_SetItemString(self->x_attr, name, v);
}


/* --------------------------------------------------------------------- */

/* Function of two integers returning integer */

PyDoc_STRVAR(xx_foo_doc,
             "foo(i,j)\n\nReturn the sum of i and j.");

static PyObject *
xx_foo(PyObject *self, PyObject *args)
{
    long i, j;
    long res;
    if (!PyArg_ParseTuple(args, "ll:foo", &i, &j))
        return NULL;
    res = i+j; /* XXX Do something here */
    return PyLong_FromLong(res);
}


/* Function of no arguments returning new Xxo object */

static PyObject *
xx_new(PyObject *self, PyObject *args)
{
    XxoObject *rv;

    if (!PyArg_ParseTuple(args, ":new"))
        return NULL;
    rv = newXxoObject(args);
    if (rv == NULL)
        return NULL;
    return (PyObject *)rv;
}

/* Example with subtle bug from extensions manual ("Thin Ice"). */

static PyObject *
xx_bug(PyObject *self, PyObject *args)
{
    PyObject *list, *item;

    if (!PyArg_ParseTuple(args, "O:bug", &list))
        return NULL;

    item = PyList_GetItem(list, 0);
    /* Py_INCREF(item); */
    PyList_SetItem(list, 1, PyLong_FromLong(0L));
    PyObject_Print(item, stdout, 0);
    printf("\n");
    /* Py_DECREF(item); */

    Py_INCREF(Py_None);
    return Py_None;
}

/* Test bad format character */

static PyObject *
xx_roj(PyObject *self, PyObject *args)
{
    PyObject *a;
    long b;
    if (!PyArg_ParseTuple(args, "O#:roj", &a, &b))
        return NULL;
    Py_INCREF(Py_None);
    return Py_None;
}

/* Test pass pyobject to c and c extract it */
static PyObject *
xx_pass(PyObject *self, PyObject *args)
{
    PyObject *obj;
    if (!PyArg_ParseTuple(args, "O", &obj))
        return NULL;
    {
        PyObject *attr_name = Py_BuildValue("s","tup");
        assert(PyObject_HasAttr(obj,attr_name));
        PyObject *obj_attr = PyObject_GetAttr(obj,attr_name);

        int integer=0;
        const char *str = NULL;
        PyObject* list;
        PyArg_ParseTuple(obj_attr,"Ois",&list,&integer,&str);



        int a,b;
        PyObject* item0 = PyList_GetItem(list,0);
        PyObject* item1 = PyList_GetItem(list,1);
        PyArg_Parse(item0,"i",&a);
        PyArg_Parse(item1,"i",&b);
        printf("obj.integer: %d\n"
               "obj.string: %s\n"
               "obj.feature[0]: %d\n"
               "obj.feature[1]: %d\n",
               integer,str,a,b);
    }

    Py_INCREF(Py_None);
    return Py_None;

}


class SimpleTimer
{
    struct timeval st_tm, end_tm;
    float calcTime(timeval start, timeval end)
    {
        return (1000000*(end.tv_sec-start.tv_sec) + end.tv_usec-start.tv_usec) * 1.0 / 1000;
    }

public:
    SimpleTimer() {
        gettimeofday(&st_tm, NULL);
    }
    ~SimpleTimer(){
        gettimeofday(&end_tm, NULL);
        printf("%fms elapsed\n", calcTime(st_tm, end_tm));
    }
};


/* Test List efficiency */
#define LOOP_TIMES 100000

#define PRINT_OPERATION(OPERATION) printf("\n\t"#OPERATION":\n\t")
#define PRINT_TARGET(TARGET) printf("test "#TARGET": \n")

static PyObject *
xx_efficiencyList(PyObject *self, PyObject *args)
{
    PyObject *obj;
    if (!PyArg_ParseTuple(args, "O", &obj))
        return NULL;

    int flag;
    PyArg_Parse(obj,"i",&flag);

    switch (flag) {
    case 0:
    {
        PRINT_TARGET(PyList);
        PyObject* py_list = Py_BuildValue("[]");
        PRINT_OPERATION(Append);
        {
            SimpleTimer timer;
            for(int i = 0; i < LOOP_TIMES; ++i)
            {
                PyObject* py_list_item = Py_BuildValue("i",i);
                int ret = PyList_Append(py_list,py_list_item);
                assert(ret==0);
            }
        }
        PRINT_OPERATION(Random Access);
        {
            SimpleTimer timer;

            for(int i=0; i<LOOP_TIMES; ++i)
            {
                PyObject* item = PyList_GetItem(py_list,i);
                int a;
                PyArg_Parse(item,"i",&a);
                assert(a>=0);
            }
        }
        PRINT_OPERATION(Insert);
        {
            SimpleTimer timer;

            for(int i = 0; i<LOOP_TIMES; ++i)
            {
                PyObject* item = Py_BuildValue("i",i);
                int ret = PyList_Insert(py_list,LOOP_TIMES/2,item);
                assert(ret == 0);
            }
        }

        Py_DecRef(py_list);

        break;
    }

    case 1:
    {
        PRINT_TARGET(std::list);
        using namespace std;
        list<int> std_list;
        PRINT_OPERATION(Append);
        {
            SimpleTimer timer;

            for(int i=0; i<LOOP_TIMES; ++i)
            {
                std_list.push_back(i);
            }
        }
        PRINT_OPERATION(Random Access);
        {
            SimpleTimer timer;

            for(int i=0; i<LOOP_TIMES; ++i)
            {
                int j =0;
                for(list<int>::iterator it = std_list.begin(); it!=std_list.end(); ++j,++it)
                {
                    if(i == j)
                    {
                        int a = *it;
                        (void)a;
                        *it = 0;
                        break;
                    }
                }
            }

        }
        PRINT_OPERATION(Insert);
        {
            SimpleTimer timer;
            list<int>::iterator it=std_list.begin();
            for(int i=0; i<LOOP_TIMES/2; ++i)
            {
                it++;
            }
            for(int i=0; i<LOOP_TIMES; ++i)
            {
                it = std_list.insert(it,1);
            }
        }

        break;
    }

    case 2:
    {
        PRINT_TARGET(std::vector);
        using namespace std;
        vector<int> std_vector;
        PRINT_OPERATION(Append);
        {
            SimpleTimer timer;
            for(int i=0; i<LOOP_TIMES; ++i)
            {
                std_vector.push_back(i);
            }
        }
        PRINT_OPERATION(Random Access);
        {
            SimpleTimer timer;
            for(int i=0; i<LOOP_TIMES; ++i)
            {
                std_vector[i]=1;
            }
        }
        PRINT_OPERATION(Insert);
        {
            SimpleTimer timer;
            vector<int>::iterator it=std_vector.begin();
            it+=LOOP_TIMES/2;
            for(int i=0; i<LOOP_TIMES; ++i)
            {
                it = std_vector.insert(it,1);
            }

        }

        break;
    }
    default:

        break;
    }

    printf("\n");
    Py_INCREF(Py_None);
    return Py_None;
}


/* ---------- */

static PyTypeObject Str_Type = {
    /* The ob_type field must be initialized in the module init function
         * to be portable to Windows without using C++. */
    PyVarObject_HEAD_INIT(NULL, 0)
    "xxmodule.Str",             /*tp_name*/
    0,                          /*tp_basicsize*/
    0,                          /*tp_itemsize*/
    /* methods */
    0,                          /*tp_dealloc*/
    0,                          /*tp_print*/
    0,                          /*tp_getattr*/
    0,                          /*tp_setattr*/
    0,                          /*tp_reserved*/
    0,                          /*tp_repr*/
    0,                          /*tp_as_number*/
    0,                          /*tp_as_sequence*/
    0,                          /*tp_as_mapping*/
    0,                          /*tp_hash*/
    0,                          /*tp_call*/
    0,                          /*tp_str*/
    0,                          /*tp_getattro*/
    0,                          /*tp_setattro*/
    0,                          /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /*tp_flags*/
    0,                          /*tp_doc*/
    0,                          /*tp_traverse*/
    0,                          /*tp_clear*/
    0,                          /*tp_richcompare*/
    0,                          /*tp_weaklistoffset*/
    0,                          /*tp_iter*/
    0,                          /*tp_iternext*/
    0,                          /*tp_methods*/
    0,                          /*tp_members*/
    0,                          /*tp_getset*/
    0, /* see PyInit_xx */      /*tp_base*/
    0,                          /*tp_dict*/
    0,                          /*tp_descr_get*/
    0,                          /*tp_descr_set*/
    0,                          /*tp_dictoffset*/
    0,                          /*tp_init*/
    0,                          /*tp_alloc*/
    0,                          /*tp_new*/
    0,                          /*tp_free*/
    0,                          /*tp_is_gc*/
};

/* ---------- */

static PyObject *
null_richcompare(PyObject *self, PyObject *other, int op)
{
    Py_INCREF(Py_NotImplemented);
    return Py_NotImplemented;
}

static PyTypeObject Null_Type = {
    /* The ob_type field must be initialized in the module init function
         * to be portable to Windows without using C++. */
    PyVarObject_HEAD_INIT(NULL, 0)
    "xxmodule.Null",            /*tp_name*/
    0,                          /*tp_basicsize*/
    0,                          /*tp_itemsize*/
    /* methods */
    0,                          /*tp_dealloc*/
    0,                          /*tp_print*/
    0,                          /*tp_getattr*/
    0,                          /*tp_setattr*/
    0,                          /*tp_reserved*/
    0,                          /*tp_repr*/
    0,                          /*tp_as_number*/
    0,                          /*tp_as_sequence*/
    0,                          /*tp_as_mapping*/
    0,                          /*tp_hash*/
    0,                          /*tp_call*/
    0,                          /*tp_str*/
    0,                          /*tp_getattro*/
    0,                          /*tp_setattro*/
    0,                          /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /*tp_flags*/
    0,                          /*tp_doc*/
    0,                          /*tp_traverse*/
    0,                          /*tp_clear*/
    null_richcompare,           /*tp_richcompare*/
    0,                          /*tp_weaklistoffset*/
    0,                          /*tp_iter*/
    0,                          /*tp_iternext*/
    0,                          /*tp_methods*/
    0,                          /*tp_members*/
    0,                          /*tp_getset*/
    0, /* see PyInit_xx */      /*tp_base*/
    0,                          /*tp_dict*/
    0,                          /*tp_descr_get*/
    0,                          /*tp_descr_set*/
    0,                          /*tp_dictoffset*/
    0,                          /*tp_init*/
    0,                          /*tp_alloc*/
    PyType_GenericNew,          /*tp_new*/
    0,                          /*tp_free*/
    0,                          /*tp_is_gc*/
};


/* ---------- */


/* List of functions defined in the module */

static PyMethodDef xx_methods[] = {
    {"roj",             xx_roj,         METH_VARARGS,
     PyDoc_STR("roj(a,b) -> None")},
    {"foo",             xx_foo,         METH_VARARGS,
     xx_foo_doc},
    {"new",             xx_new,         METH_VARARGS,
     PyDoc_STR("new() -> new Xx object")},
    {"bug",             xx_bug,         METH_VARARGS,
     PyDoc_STR("bug(o) -> None")},
    {"Pass",            xx_pass,        METH_VARARGS,
     PyDoc_STR("Pass(o) -> None")},
    {"efficiencyList",  xx_efficiencyList, METH_VARARGS,
     PyDoc_STR("efficiencyList(i) -> None, i: 0:PyList;1:std::list;2:std::vector")},
    {NULL,              NULL}           /* sentinel */
};

PyDoc_STRVAR(module_doc,
             "This is a template module just for instruction.");


static int
xx_exec(PyObject *m)
{
    /* Slot initialization is subject to the rules of initializing globals.
       C99 requires the initializers to be "address constants".  Function
       designators like 'PyType_GenericNew', with implicit conversion to
       a pointer, are valid C99 address constants.

       However, the unary '&' operator applied to a non-static variable
       like 'PyBaseObject_Type' is not required to produce an address
       constant.  Compilers may support this (gcc does), MSVC does not.

       Both compilers are strictly standard conforming in this particular
       behavior.
    */
    Null_Type.tp_base = &PyBaseObject_Type;
    Str_Type.tp_base = &PyUnicode_Type;

    /* Finalize the type object including setting type of the new type
     * object; doing it here is required for portability, too. */
    if (PyType_Ready(&Xxo_Type) < 0)
        goto fail;

    /* Add some symbolic constants to the module */
    if (ErrorObject == NULL) {
        ErrorObject = PyErr_NewException("xx.error", NULL, NULL);
        if (ErrorObject == NULL)
            goto fail;
    }
    Py_INCREF(ErrorObject);
    PyModule_AddObject(m, "error", ErrorObject);

    /* Add Str */
    if (PyType_Ready(&Str_Type) < 0)
        goto fail;
    PyModule_AddObject(m, "Str", (PyObject *)&Str_Type);

    /* Add Null */
    if (PyType_Ready(&Null_Type) < 0)
        goto fail;
    PyModule_AddObject(m, "Null", (PyObject *)&Null_Type);
    return 0;
fail:
    Py_XDECREF(m);
    return -1;
}

static struct PyModuleDef_Slot xx_slots[] = {
{Py_mod_exec, (void*)xx_exec},
{0, NULL},
};

static struct PyModuleDef xxmodule = {
    PyModuleDef_HEAD_INIT,
    "xx",
    module_doc,
    0,
    xx_methods,
    xx_slots,
    NULL,
    NULL,
    NULL
};

/* Export function for the module (*must* be called PyInit_xx) */

PyMODINIT_FUNC
PyInit_xx(void)
{
    return PyModuleDef_Init(&xxmodule);
}

