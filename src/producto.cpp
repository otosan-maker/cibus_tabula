#include "producto.hpp"

producto::producto(int id,const char * f_alta,const char * f_baja,const char * prod,const char * loc)
{
    m_idproducto=id;
    strncpy(m_f_alta,f_alta,MAX_FECHA);
    strncpy(m_f_baja,f_baja,MAX_FECHA);
    strncpy(m_nombreProducto,prod,MAX_NOMBRE);
    strncpy(m_localizacion,loc,MAX_LOCATION);
    m_f_alta[MAX_FECHA]=0;
    m_f_baja[MAX_FECHA]=0;
    m_nombreProducto[MAX_NOMBRE]=0;
    m_localizacion[MAX_LOCATION]=0;
    m_seleccionado=false;
}

void producto::set(int id,const char * f_alta,const char * f_baja,const char * prod,const char * loc){
    m_idproducto=id;
    strncpy(m_f_alta,f_alta,MAX_FECHA);
    strncpy(m_f_baja,f_baja,MAX_FECHA);
    strncpy(m_nombreProducto,prod,MAX_NOMBRE);
    strncpy(m_localizacion,loc,MAX_LOCATION);
    m_f_alta[MAX_FECHA]=0;
    m_f_baja[MAX_FECHA]=0;
    m_nombreProducto[MAX_NOMBRE]=0;
    m_localizacion[MAX_LOCATION]=0;
    m_seleccionado=false;
}

producto::producto(){
    m_idproducto=0;
    m_f_alta[MAX_FECHA]=0;
    m_f_baja[MAX_FECHA]=0;
    m_nombreProducto[MAX_NOMBRE]=0;
    m_localizacion[MAX_LOCATION]=0;
    m_seleccionado=false;
}

producto::~producto(){
}