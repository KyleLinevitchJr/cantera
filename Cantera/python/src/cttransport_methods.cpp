
/**
 * Create a new Transport object.
 */
static PyObject *
py_transport_new(PyObject *self, PyObject *args) {
    char* model;
    int ph;
    int loglevel;
    if (!PyArg_ParseTuple(args, "sii:transport_new", &model, 
            &ph, &loglevel)) 
        return NULL;
    int n = newTransport(model, ph, loglevel);
    if (n < 0) return reportError(n);
    return Py_BuildValue("i",n);
}


/**
 * Delete the Phase object.
 */
static PyObject*
py_transport_delete(PyObject *self, PyObject *args)
{
    int tr;
    if (!PyArg_ParseTuple(args, "i:transport_delete", &tr)) 
        return NULL;    
    delTransport(tr);
    return Py_BuildValue("i",0);
}


static PyObject*
py_setParameters(PyObject *self, PyObject *args) {
    int n, k, typ;
    PyObject* parray;
    if (!PyArg_ParseTuple(args, "iiiO:py_setParameters", 
            &n, &typ, &k, &parray)) return NULL;

    PyArrayObject* a = (PyArrayObject*)
      PyArray_ContiguousFromObject(parray, PyArray_DOUBLE, 1, 1);
    double* xd = (double*)a->data;
    int ok = trans_setParameters(n, typ, k, xd);
    Py_DECREF(a);
    if (ok < 0) return reportError(ok);
    return Py_BuildValue("i",ok);        
}


static PyObject*
py_viscosity(PyObject *self, PyObject *args) {
    int n;
    if (!PyArg_ParseTuple(args, "i:py_viscosity", &n)) return NULL;
    double mu = trans_viscosity(n);        
    if (mu < 0.0) return reportError(int(mu));
    return Py_BuildValue("d",mu);        
}

static PyObject*
py_thermalConductivity(PyObject *self, PyObject *args) {
    int n;
    if (!PyArg_ParseTuple(args, "i:py_thermalConductivity", &n)) return NULL;
    double lambda = trans_thermalConductivity(n);
    if (lambda < 0.0) return reportError(int(lambda));
    return Py_BuildValue("d",lambda);
}

static PyObject*
py_thermalDiffCoeffs(PyObject *self, PyObject *args) {
    int n, idt;
    if (!PyArg_ParseTuple(args, "ii:py_thermalDiffCoeffs", &n, &idt)) 
        return NULL;
    PyArrayObject* dt = 
        (PyArrayObject*)PyArray_FromDims(1, &idt, PyArray_DOUBLE);
    int iok = trans_getThermalDiffCoeffs(n, idt, (double*)dt->data);
    if (iok < 0) return reportError(iok);
    return PyArray_Return(dt);
}

static PyObject*
py_binaryDiffCoeffs(PyObject *self, PyObject *args) {
    int n, id;
    if (!PyArg_ParseTuple(args, "ii:py_binaryDiffCoeffs", &n, &id)) 
        return NULL;
    int idim[2];
    idim[0] = id;
    idim[1] = id;
    PyArrayObject* d = 
        (PyArrayObject*)PyArray_FromDims(2, idim, PyArray_DOUBLE);
    int iok = trans_getBinDiffCoeffs(n, id, (double*)d->data);
    if (iok < 0) return reportError(iok);
    return PyArray_Return(d);
}

static PyObject*
py_mixDiffCoeffs(PyObject *self, PyObject *args) {
    int n, id;
    if (!PyArg_ParseTuple(args, "ii:py_mixDiffCoeffs", &n, &id)) 
        return NULL;
    PyArrayObject* d = 
        (PyArrayObject*)PyArray_FromDims(1, &id, PyArray_DOUBLE);
    int iok = trans_getMixDiffCoeffs(n, id, (double*)d->data);
    if (iok < 0) return reportError(iok);
    return PyArray_Return(d);
}

static PyObject*
py_multiDiffCoeffs(PyObject *self, PyObject *args) {
    int n, id;
    if (!PyArg_ParseTuple(args, "ii:py_multiDiffCoeffs", &n, &id)) 
        return NULL;
    //vector_int idim(2,id);
    int idim[2];
    idim[0] = id;
    idim[1] = id;
    PyArrayObject* d = 
        (PyArrayObject*)PyArray_FromDims(2, idim, PyArray_DOUBLE);
    int iok = trans_getMultiDiffCoeffs(n, id, (double*)d->data);
    if (iok < 0) return reportError(iok);
    return PyArray_Return(d);
}


