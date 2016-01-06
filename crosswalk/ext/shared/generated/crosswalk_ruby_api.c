#include "ruby.h"

static VALUE rb_api_mParent;
static VALUE rb_api_mCrosswalk;

VALUE rb_Crosswalk_getProperty(int argc, VALUE *argv, VALUE obj);
VALUE rb_s_Crosswalk_def_getProperty(int argc, VALUE *argv);
VALUE rb_Crosswalk_getProperties(int argc, VALUE *argv, VALUE obj);
VALUE rb_s_Crosswalk_def_getProperties(int argc, VALUE *argv);
VALUE rb_Crosswalk_getAllProperties(int argc, VALUE *argv, VALUE obj);
VALUE rb_s_Crosswalk_def_getAllProperties(int argc, VALUE *argv);
VALUE rb_Crosswalk_setProperty(int argc, VALUE *argv, VALUE obj);
VALUE rb_s_Crosswalk_def_setProperty(int argc, VALUE *argv);
VALUE rb_Crosswalk_setProperties(int argc, VALUE *argv, VALUE obj);
VALUE rb_s_Crosswalk_def_setProperties(int argc, VALUE *argv);



VALUE rb_Crosswalk_s_default(VALUE klass);
VALUE rb_Crosswalk_s_setDefault(VALUE klass, VALUE obj);


VALUE getRuby_Crosswalk_Module(){ return rb_api_mCrosswalk; }



static void _free_class_object(void *p)
{
    ruby_xfree(p);
}

static VALUE _allocate_class_object(VALUE klass)
{
    VALUE valObj = 0;
    char ** ppString = NULL;
    void* pData = ALLOC(void*);
    memset( pData, 0, sizeof(pData) );
    
	valObj = Data_Wrap_Struct(klass, 0, _free_class_object, pData);

    Data_Get_Struct(valObj, char *, ppString);
    *ppString = xmalloc(10);
    sprintf(*ppString, "%X", valObj);

    return valObj;
}

void Init_RubyAPI_Crosswalk(void)
{

    VALUE tmpParent = Qnil;
    rb_api_mParent = rb_define_module("Rho");
    

	rb_api_mCrosswalk = rb_define_class_under(rb_api_mParent, "Crosswalk", rb_cObject);

	rb_define_alloc_func(rb_api_mCrosswalk, _allocate_class_object);
    //Constructor should be not available in case of static members
    //rb_undef_alloc_func(rb_api_mCrosswalk);

    rb_define_method(rb_api_mCrosswalk, "getProperty", rb_Crosswalk_getProperty, -1);
    rb_define_singleton_method(rb_api_mCrosswalk, "getProperty", rb_s_Crosswalk_def_getProperty, -1);
    rb_define_method(rb_api_mCrosswalk, "getProperties", rb_Crosswalk_getProperties, -1);
    rb_define_singleton_method(rb_api_mCrosswalk, "getProperties", rb_s_Crosswalk_def_getProperties, -1);
    rb_define_method(rb_api_mCrosswalk, "getAllProperties", rb_Crosswalk_getAllProperties, -1);
    rb_define_singleton_method(rb_api_mCrosswalk, "getAllProperties", rb_s_Crosswalk_def_getAllProperties, -1);
    rb_define_method(rb_api_mCrosswalk, "setProperty", rb_Crosswalk_setProperty, -1);
    rb_define_singleton_method(rb_api_mCrosswalk, "setProperty", rb_s_Crosswalk_def_setProperty, -1);
    rb_define_method(rb_api_mCrosswalk, "setProperties", rb_Crosswalk_setProperties, -1);
    rb_define_singleton_method(rb_api_mCrosswalk, "setProperties", rb_s_Crosswalk_def_setProperties, -1);



    rb_define_singleton_method(rb_api_mCrosswalk, "getDefault", rb_Crosswalk_s_default, 0);
    rb_define_singleton_method(rb_api_mCrosswalk, "setDefault", rb_Crosswalk_s_setDefault, 1);






}

