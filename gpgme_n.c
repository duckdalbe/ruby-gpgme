/* gpgme_n.c -- low level interface to GPGME
   Copyright (C) 2003,2006 Daiki Ueno

This file is a part of Ruby-GPGME.

This program is free software; you can redistribute it and/or modify 
it under the terms of the GNU General Public License as published by 
the Free Software Foundation; either version 2, or (at your option)  
any later version.                                                   

This program is distributed in the hope that it will be useful,      
but WITHOUT ANY WARRANTY; without even the implied warranty of       
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the        
GNU General Public License for more details.                         

You should have received a copy of the GNU General Public License    
along with GNU Emacs; see the file COPYING.  If not, write to the    
Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
Boston, MA 02110-1301, USA.  */

/* This file is (semi) automatically generated, though it was written
   by hand :-) There are simple rules.

1. Each symbol exported from this module is either a class, a module
   function, or a constant.  No instance methods are defined here.
2. Each symbol exported from this module follows the same naming
   convention of the library API.  That is, symbol names are followed
   by `gpgme_' for functions and are followed by `GPGME_' or `GPG_' for
   constants.
3. Output arguments are wrapped in arrays.  For example, the 1st
   argument of `gpgme_data_new' has type `gpgme_data_t *' to store the
   newly created gpgme_data_t object.  The corresponding ruby
   interface uses an empty array to passing it to the caller.  */

#include "ruby.h"
#include "gpgme.h"
#include <errno.h>

/* StringValuePtr is not available in 1.6. */
#ifndef StringValuePtr
#define StringValuePtr(str) RSTRING(str)->ptr
#endif

/* STR2CSTR is obsoleted in 1.8. */
#ifndef StringValueCStr
#define StringValueCStr STR2CSTR
#endif

/* RARRAY_LEN is not available in 1.8. */
#ifndef RARRAY_LEN
#define RARRAY_LEN(a) RARRAY(a)->len
#endif

/* RARRAY_PTR is not available in 1.8. */
#ifndef RARRAY_PTR
#define RARRAY_PTR(a) RARRAY(a)->ptr
#endif

#define WRAP_GPGME_DATA(dh)					\
  Data_Wrap_Struct(cGpgmeData, 0, gpgme_data_release, dh)	\
/* `gpgme_data_t' is typedef'ed as `struct gpgme_data *'. */
#define UNWRAP_GPGME_DATA(vdh, dh)				\
  Data_Get_Struct(vdh, struct gpgme_data, dh);

#define WRAP_GPGME_CTX(ctx)					\
  Data_Wrap_Struct(cGpgmeCtx, 0, gpgme_release, ctx)		\
/* `gpgme_ctx_t' is typedef'ed as `struct gpgme_context *'. */
#define UNWRAP_GPGME_CTX(vctx, ctx)				\
  Data_Get_Struct(vctx, struct gpgme_context, ctx)

#define WRAP_GPGME_KEY(key)					\
  Data_Wrap_Struct(cGpgmeKey, 0, gpgme_key_release, key)	\
/* `gpgme_key_t' is typedef'ed as `struct _gpgme_key *'. */
#define UNWRAP_GPGME_KEY(vkey, key)				\
  Data_Get_Struct(vkey, struct _gpgme_key, key)

#define WRAP_GPGME_TRUST_ITEM(item)					  \
  Data_Wrap_Struct(cGpgmeTrustItem, 0, gpgme_trust_item_release, item)	  \
/* `gpgme_trust_item_t' is typedef'ed as `struct _gpgme_trust_item *'. */
#define UNWRAP_GPGME_TRUST_ITEM(vitem, item)				  \
  Data_Get_Struct(vitem, struct _gpgme_trust_item, item)

static VALUE cGpgmeEngineInfo,
  cGpgmeCtx,
  cGpgmeData,
  cGpgmeKey,
  cGpgmeSubKey,
  cGpgmeUserId,
  cGpgmeKeySig,
  cGpgmeVerifyResult,
  cGpgmeSignature,
  cGpgmeSigNotation,
  cGpgmeTrustItem;

static VALUE
rb_s_gpgme_check_version (dummy, vreq)
     VALUE dummy, vreq;
{
  const char *result = gpgme_check_version (NIL_P(vreq) ? NULL :
					    StringValueCStr(vreq));
  return result ? rb_str_new2 (result) : Qnil;
}

static VALUE
rb_s_gpgme_engine_check_version (dummy, vproto)
     VALUE dummy, vproto;
{
  gpgme_error_t err = gpgme_engine_check_version (NUM2INT(vproto));
  return LONG2NUM(err);
}

static VALUE
rb_s_gpgme_get_engine_info (dummy, rinfo)
     VALUE dummy, rinfo;
{
  gpgme_engine_info_t info;
  gpgme_error_t err;

  err = gpgme_get_engine_info (&info);
  if (gpgme_err_code(err) == GPG_ERR_NO_ERROR)
    {
      for (; info; info = info->next)
	{
	  VALUE vinfo = rb_class_new_instance (0, NULL, cGpgmeEngineInfo);
	  rb_iv_set (vinfo, "@protocol", INT2FIX(info->protocol));
	  if (info->file_name)
	    rb_iv_set (vinfo, "@file_name", rb_str_new2 (info->file_name));
	  if (info->version)
	    rb_iv_set (vinfo, "@version", rb_str_new2 (info->version));
	  if (info->req_version)
	    rb_iv_set (vinfo, "@req_version", rb_str_new2 (info->req_version));
	  rb_ary_push (rinfo, vinfo);
	}
    }
  return LONG2NUM(err);
}

static VALUE
rb_s_gpgme_err_code (dummy, verr)
     VALUE dummy, verr;
{
  return INT2FIX(gpgme_err_code (NUM2LONG(verr)));
}

static VALUE
rb_s_gpgme_err_source (dummy, verr)
     VALUE dummy, verr;
{
  return INT2FIX(gpgme_err_source (NUM2LONG(verr)));
}

static VALUE
rb_s_gpgme_strerror (dummy, verr)
     VALUE dummy, verr;
{
  return rb_str_new2 (gpgme_strerror (NUM2LONG(verr)));
}

static VALUE
rb_s_gpgme_data_new (dummy, rdh)
     VALUE dummy, rdh;
{
  gpgme_data_t dh;
  gpgme_error_t err = gpgme_data_new (&dh);

  if (gpgme_err_code(err) == GPG_ERR_NO_ERROR)
    rb_ary_push (rdh, WRAP_GPGME_DATA(dh));
  return LONG2NUM(err);
}  

static VALUE
rb_s_gpgme_data_new_from_mem (dummy, rdh, vbuffer, vsize, vcopy)
     VALUE dummy, rdh, vbuffer, vsize, vcopy;
{
  gpgme_data_t dh;
  VALUE vdh;
  size_t size = NUM2UINT(vsize);
  gpgme_error_t err;

  if (RSTRING(vbuffer)->len < size)
    rb_raise (rb_eArgError, "argument out of range");

  rb_str_modify (vbuffer);
  err = gpgme_data_new_from_mem (&dh, StringValuePtr(vbuffer), size,
				 NUM2INT(vcopy));
  if (gpgme_err_code(err) == GPG_ERR_NO_ERROR)
    {
      vdh = WRAP_GPGME_DATA(dh);
      /* Keep a references to VBUFFER to avoid GC. */
      rb_iv_set (vdh, "@buffer", vbuffer);
      rb_ary_push (rdh, vdh);
    }
  return LONG2NUM(err);
}  

static VALUE
rb_s_gpgme_data_new_from_file (dummy, rdh, vfilename, vcopy)
     VALUE dummy, rdh, vfilename, vcopy;
{
  gpgme_data_t dh;
  gpgme_error_t err = gpgme_data_new_from_file (&dh,
						StringValueCStr(vfilename),
						NUM2INT(vcopy));
  if (gpgme_err_code(err) == GPG_ERR_NO_ERROR)
    rb_ary_push (rdh, WRAP_GPGME_DATA(dh));
  return LONG2NUM(err);
}

static VALUE
rb_s_gpgme_data_new_from_fd (dummy, rdh, vfd)
     VALUE dummy, rdh, vfd;
{
  gpgme_data_t dh;
  gpgme_error_t err = gpgme_data_new_from_fd (&dh, NUM2INT(vfd));
  if (gpgme_err_code(err) == GPG_ERR_NO_ERROR)
    rb_ary_push (rdh, WRAP_GPGME_DATA(dh));
  return LONG2NUM(err);
}

static ssize_t
read_cb (handle, buffer, size)
     void *handle;
     char *buffer;
     size_t size;
{
  VALUE vcb = (VALUE)handle, vcbs, vhook_value, vbuffer;

  vcbs = RARRAY(vcb)->ptr[0];
  vhook_value = RARRAY(vcb)->ptr[1];

  vbuffer = rb_funcall (vcbs, rb_intern ("read"), 2, vhook_value,
			LONG2NUM(size));
  if (NIL_P(vbuffer))
    return -1;
  memcpy (buffer, StringValuePtr(vbuffer), RSTRING(vbuffer)->len);
  return RSTRING(vbuffer)->len;
}

static ssize_t
write_cb (handle, buffer, size)
     void *handle;
     char *buffer;
     size_t size;
{
  VALUE vcb = (VALUE)handle, vcbs, vhook_value, vbuffer, vnwrite;

  vcbs = RARRAY(vcb)->ptr[0];
  vhook_value = RARRAY(vcb)->ptr[1];
  vbuffer = rb_str_new (buffer, size);

  vnwrite = rb_funcall (vcbs, rb_intern ("write"), 3,
			vhook_value, vbuffer, LONG2NUM(size));
  return NUM2LONG(vnwrite);
}

static off_t
seek_cb (handle, offset, whence)
     void *handle;
     off_t offset;
     int whence;
{
  VALUE vcb = (VALUE)handle, vcbs, vhook_value, vpos;
  ID id_seek = rb_intern ("seek");

  vcbs = RARRAY(vcb)->ptr[0];
  vhook_value = RARRAY(vcb)->ptr[1];

  if (rb_respond_to (vcbs, id_seek))
    {
      vpos = rb_funcall (vcbs, id_seek, 3,
			 vhook_value, LONG2NUM(offset), INT2FIX(whence));
      return NUM2LONG(vpos);
    }
  errno = ENOSYS;
  return -1;
}

static VALUE
rb_s_gpgme_data_new_from_cbs (dummy, rdh, vcbs, vhandle)
     VALUE dummy, rdh, vcbs, vhandle;
{
  gpgme_data_t dh;
  gpgme_error_t err;
  struct gpgme_data_cbs cbs;
  VALUE vcbs_handle = rb_ary_new ();

  cbs.read = read_cb;
  cbs.write = write_cb;
  cbs.seek = seek_cb;
  cbs.release = NULL;

  rb_ary_push (vcbs_handle, vcbs);
  rb_ary_push (vcbs_handle, vhandle);

  err = gpgme_data_new_from_cbs (&dh, &cbs, (void*)vcbs_handle);
  if (gpgme_err_code(err) == GPG_ERR_NO_ERROR)
    {
      VALUE vdh = WRAP_GPGME_DATA(dh);
      /* Keep a references to avoid GC. */
      rb_iv_set (vdh, "@cbs_handle", vcbs_handle);
      rb_ary_push (rdh, vdh);
    }
  return LONG2NUM(err);
}

static VALUE
rb_s_gpgme_data_release (dummy, vdh)
     VALUE dummy, vdh;
{
  gpgme_data_t dh;

  UNWRAP_GPGME_DATA(vdh, dh);
  if (!dh)
    rb_raise (rb_eRuntimeError,
	      "GpgmeData has already been released.");
  gpgme_data_release (dh);
  DATA_PTR(vdh) = NULL;
  return Qnil;
}

static VALUE
rb_s_gpgme_data_release_and_get_mem (dummy, vdh, rlength)
     VALUE dummy, vdh, rlength;
{
  gpgme_data_t dh;
  char *buffer;
  VALUE vbuffer;
  size_t length;

  UNWRAP_GPGME_DATA(vdh, dh);
  if (!dh)
    rb_raise (rb_eRuntimeError,
      "GpgmeData has already been released.");
  buffer = gpgme_data_release_and_get_mem (dh, &length);
  DATA_PTR(vdh) = NULL;
  if (buffer == NULL)
    return Qnil;
  vbuffer = rb_str_new (buffer, length);
  free (buffer);
  rb_ary_push (rlength, UINT2NUM(length));
  return vbuffer;
}

static VALUE
rb_s_gpgme_data_read (dummy, vdh, rbuffer, vlength)
     VALUE dummy, vdh, rbuffer, vlength;
{
  gpgme_data_t dh;
  ssize_t length = NUM2LONG(vlength), nread;

  if (!NIL_P(rbuffer))
    {
      if (RSTRING(rbuffer)->len < length)
	rb_raise (rb_eArgError, "argument out of range");
      rb_str_modify (rbuffer);
    }
  UNWRAP_GPGME_DATA(vdh, dh);
  nread = gpgme_data_read (dh, NIL_P(rbuffer) ? NULL : StringValuePtr(rbuffer),
			   length);
  if (nread < 0)
    rb_sys_fail ("rb_s_gpgme_data_read");
  return LONG2NUM(nread);
}

static VALUE
rb_s_gpgme_data_seek (dummy, vdh, voffset, vwhence)
     VALUE dummy, vdh, voffset, vwhence;
{
  gpgme_data_t dh;
  off_t pos;

  UNWRAP_GPGME_DATA(vdh, dh);
  pos = gpgme_data_seek (dh, NUM2LONG(voffset), NUM2INT(vwhence));
  if (pos < 0)
    rb_sys_fail ("rb_s_gpgme_data_seek");
  return LONG2NUM(pos);
}

static VALUE
rb_s_gpgme_data_write (dummy, vdh, vbuf, vlen)
     VALUE dummy, vdh, vbuf, vlen;
{
  gpgme_data_t dh;
  ssize_t nwrite;

  UNWRAP_GPGME_DATA(vdh, dh);
  nwrite = gpgme_data_write (dh, StringValuePtr(vbuf), NUM2UINT(vlen));
  if (nwrite < 0)
    rb_sys_fail ("rb_s_gpgme_data_write");
  return LONG2NUM(nwrite);
}

static VALUE
rb_s_gpgme_data_get_encoding (dummy, vdh)
     VALUE dummy, vdh;
{
  gpgme_data_t dh;
  gpgme_error_t err;

  UNWRAP_GPGME_DATA(vdh, dh);
  err = gpgme_data_get_encoding (dh);
  return LONG2NUM(err);
}

static VALUE
rb_s_gpgme_data_set_encoding (dummy, vdh, venc)
     VALUE dummy, vdh, venc;
{
  gpgme_data_t dh;
  gpgme_error_t err;

  UNWRAP_GPGME_DATA(vdh, dh);
  err = gpgme_data_set_encoding (dh, NUM2INT(venc));
  return LONG2NUM(err);
}

static VALUE
rb_s_gpgme_new (dummy, rctx)
     VALUE dummy, rctx;
{
  gpgme_ctx_t ctx;
  gpgme_error_t err = gpgme_new (&ctx);

  if (gpgme_err_code(err) == GPG_ERR_NO_ERROR)
    rb_ary_push (rctx, WRAP_GPGME_CTX(ctx));
  return LONG2NUM(err);
}

static VALUE
rb_s_gpgme_release (dummy, vctx)
     VALUE dummy, vctx;
{
  gpgme_ctx_t ctx;

  UNWRAP_GPGME_CTX(vctx, ctx);
  if (!ctx)
    rb_raise (rb_eRuntimeError,
      "gpgme_ctx_t has already been released.");
  gpgme_release (ctx);
  DATA_PTR(vctx) = NULL;
  return Qnil;
}

static VALUE
rb_s_gpgme_set_protocol (dummy, vctx, vproto)
     VALUE dummy, vctx, vproto;
{
  gpgme_ctx_t ctx;
  gpgme_error_t err;

  UNWRAP_GPGME_CTX(vctx, ctx);
  err = gpgme_set_protocol (ctx, NUM2INT(vproto));
  return LONG2NUM(err);
}

static VALUE
rb_s_gpgme_get_protocol (dummy, vctx)
     VALUE dummy, vctx;
{
  gpgme_ctx_t ctx;
  gpgme_protocol_t proto;

  UNWRAP_GPGME_CTX(vctx, ctx);
  proto = gpgme_get_protocol (ctx);
  return INT2NUM(proto);
}

static VALUE
rb_s_gpgme_set_armor (dummy, vctx, vyes)
     VALUE dummy, vctx, vyes;
{
  gpgme_ctx_t ctx;

  UNWRAP_GPGME_CTX(vctx, ctx);
  gpgme_set_armor (ctx, NUM2INT(vyes));

  return Qnil;
}

static VALUE
rb_s_gpgme_get_armor (dummy, vctx)
     VALUE dummy, vctx;
{
  gpgme_ctx_t ctx;
  int yes;

  UNWRAP_GPGME_CTX(vctx, ctx);
  yes = gpgme_get_armor (ctx);
  return INT2NUM(yes);
}

static VALUE
rb_s_gpgme_set_textmode (dummy, vctx, vyes)
     VALUE dummy, vctx, vyes;
{
  gpgme_ctx_t ctx;

  UNWRAP_GPGME_CTX(vctx, ctx);
  gpgme_set_textmode (ctx, NUM2INT(vyes));
  return Qnil;
}     

static VALUE
rb_s_gpgme_get_textmode (dummy, vctx)
     VALUE dummy, vctx;
{
  gpgme_ctx_t ctx;
  int yes;

  UNWRAP_GPGME_CTX(vctx, ctx);
  yes = gpgme_get_textmode (ctx);
  return INT2NUM(yes);
}     

static VALUE
rb_s_gpgme_set_include_certs (dummy, vctx, vnr_of_certs)
     VALUE dummy, vctx, vnr_of_certs;
{
  gpgme_ctx_t ctx;

  UNWRAP_GPGME_CTX(vctx, ctx);
  gpgme_set_include_certs (ctx, NUM2INT(vnr_of_certs));
  return Qnil;
}

static VALUE
rb_s_gpgme_get_include_certs (dummy, vctx)
     VALUE dummy, vctx;
{
  gpgme_ctx_t ctx;
  gpgme_error_t err;

  UNWRAP_GPGME_CTX(vctx, ctx);
  err = gpgme_get_include_certs (ctx);
  return LONG2NUM(err);
}

static VALUE
rb_s_gpgme_set_keylist_mode (dummy, vctx, vmode)
     VALUE dummy, vctx, vmode;
{
  gpgme_ctx_t ctx;
  gpgme_error_t err;

  UNWRAP_GPGME_CTX(vctx, ctx);
  err = gpgme_set_keylist_mode (ctx, NUM2INT(vmode));
  return LONG2NUM(err);
}

static VALUE
rb_s_gpgme_get_keylist_mode (dummy, vctx)
     VALUE dummy, vctx;
{
  gpgme_ctx_t ctx;
  int mode;

  UNWRAP_GPGME_CTX(vctx, ctx);
  mode = gpgme_get_keylist_mode (ctx);
  return INT2NUM(mode);
}

static gpgme_error_t
passphrase_cb (hook, uid_hint, passphrase_info, prev_was_bad, fd)
     void *hook;
     const char *uid_hint, *passphrase_info;
     int prev_was_bad, fd;
{
  VALUE vcb = (VALUE)hook, vpassfunc, vhook_value, verr;

  vpassfunc = RARRAY(vcb)->ptr[0];
  vhook_value = RARRAY(vcb)->ptr[1];

  verr = rb_funcall (vpassfunc, rb_intern ("call"), 5,
		     vhook_value,
		     uid_hint ? rb_str_new2 (uid_hint) : Qnil,
		     passphrase_info ? rb_str_new2 (passphrase_info) : Qnil,
		     INT2NUM(prev_was_bad),
		     INT2NUM(fd));
  return NUM2LONG(verr);
}

static VALUE
rb_s_gpgme_set_passphrase_cb (dummy, vctx, vpassfunc, vhook_value)
     VALUE dummy, vctx, vpassfunc, vhook_value;
{
  gpgme_ctx_t ctx;
  VALUE vcb = rb_ary_new ();

  rb_ary_push (vcb, vpassfunc);
  rb_ary_push (vcb, vhook_value);
  /* Keep a references to avoid GC. */
  rb_iv_set (vctx, "@passphrase_cb", vcb);

  UNWRAP_GPGME_CTX(vctx, ctx);
  gpgme_set_passphrase_cb (ctx, passphrase_cb, (void*)vcb);
  return Qnil;
}

static VALUE
rb_s_gpgme_get_passphrase_cb (dummy, vctx, rpassfunc, rhook_value)
     VALUE dummy, vctx, rpassfunc, rhook_value;
{
  VALUE vcb = rb_iv_get (vctx, "@passphrase_cb");

  /* No need to call gpgme_get_passphrase_cb. */
  rb_ary_push (rpassfunc, RARRAY(vcb)->ptr[0]);
  rb_ary_push (rhook_value, RARRAY(vcb)->ptr[1]);
  return Qnil;
}

static void
progress_cb (hook, what, type, current, total)
     void *hook;
     const char *what;
     int type, current, total;
{
  VALUE vcb = (VALUE)hook, vprogfunc, vhook_value;

  vprogfunc = RARRAY(vcb)->ptr[0];
  vhook_value = RARRAY(vcb)->ptr[1];

  rb_funcall (vprogfunc, rb_intern ("call"), 5, vhook_value, INT2NUM(type),
	      INT2NUM(current), INT2NUM(total));
}

static VALUE
rb_s_gpgme_set_progress_cb (dummy, vctx, vprogfunc, vhook_value)
     VALUE dummy, vctx, vprogfunc, vhook_value;
{
  gpgme_ctx_t ctx;
  VALUE vcb = rb_ary_new ();

  rb_ary_push (vcb, vprogfunc);
  rb_ary_push (vcb, vhook_value);
  /* Keep a references to avoid GC. */
  rb_iv_set (vctx, "@progress_cb", vcb);

  UNWRAP_GPGME_CTX(vctx, ctx);
  gpgme_set_progress_cb (ctx, progress_cb, (void*)vctx);

  return Qnil;
}

static VALUE
rb_s_gpgme_get_progress_cb (dummy, vctx, rprogfunc, rhook_value)
     VALUE dummy, vctx, rprogfunc, rhook_value;
{
  VALUE vcb = rb_iv_get (vctx, "@progress_cb");
  rb_ary_push (rprogfunc, RARRAY(vcb)->ptr[0]);
  rb_ary_push (rhook_value, RARRAY(vcb)->ptr[1]);
  return Qnil;
}

static VALUE
rb_s_gpgme_op_keylist_start (dummy, vctx, vpattern, vsecret_only)
     VALUE dummy, vctx, vpattern, vsecret_only;
{
  gpgme_ctx_t ctx;
  gpgme_error_t err;

  UNWRAP_GPGME_CTX(vctx, ctx);
  err = gpgme_op_keylist_start (ctx, NIL_P(vpattern) ? NULL :
				StringValueCStr(vpattern),
				NUM2INT(vsecret_only));
  return LONG2NUM(err);
}

static VALUE
rb_s_gpgme_op_keylist_ext_start (dummy, vctx, vpattern, vsecret_only)
     VALUE dummy, vctx, vpattern, vsecret_only;
{
  gpgme_ctx_t ctx;
  const char **pattern = NULL;
  int i, err;

  UNWRAP_GPGME_CTX(vctx, ctx);

  if (!NIL_P(vpattern))
    {
      /* Convert RARRAY into `const char *' array. */
      pattern = (const char **)ALLOCA_N(const char *,
					RARRAY(vpattern)->len + 1);
      for (i = 0; i<RARRAY(vpattern)->len; i++)
	pattern[i] = StringValueCStr(RARRAY(vpattern)->ptr[i]);
      pattern[RARRAY(vpattern)->len] = NULL;
    }

  err = gpgme_op_keylist_ext_start (ctx, pattern, NUM2INT(vsecret_only), 0);
  return LONG2NUM(err);
}

static VALUE
wrap_gpgme_key (key)
     gpgme_key_t key;
{
  VALUE vkey = WRAP_GPGME_KEY(key), vsubkeys, vuids;
  gpgme_subkey_t subkey;
  gpgme_user_id_t user_id;

  rb_iv_set (vkey, "@keylist_mode", INT2FIX(key->keylist_mode));
  rb_iv_set (vkey, "@revoked", INT2FIX(key->revoked));
  rb_iv_set (vkey, "@expired", INT2FIX(key->expired));
  rb_iv_set (vkey, "@disabled", INT2FIX(key->disabled));
  rb_iv_set (vkey, "@invalid", INT2FIX(key->invalid));
  rb_iv_set (vkey, "@can_encrypt", INT2FIX(key->can_encrypt));
  rb_iv_set (vkey, "@can_sign", INT2FIX(key->can_sign));
  rb_iv_set (vkey, "@can_certify", INT2FIX(key->can_certify));
  rb_iv_set (vkey, "@can_authenticate", INT2FIX(key->can_authenticate));
  rb_iv_set (vkey, "@secret", INT2FIX(key->secret));
  rb_iv_set (vkey, "@protocol", INT2FIX(key->protocol));
  if (key->issuer_serial)
    rb_iv_set (vkey, "@issuer_serial", rb_str_new2 (key->issuer_serial));
  if (key->issuer_name)
    rb_iv_set (vkey, "@issuer_name", rb_str_new2 (key->issuer_name));
  if (key->chain_id)
    rb_iv_set (vkey, "@chain_id", rb_str_new2 (key->chain_id));
  rb_iv_set (vkey, "@owner_trust", INT2FIX(key->owner_trust));
  vsubkeys = rb_ary_new ();
  rb_iv_set (vkey, "@subkeys", vsubkeys);
  for (subkey = key->subkeys; subkey; subkey = subkey->next)
    {
      VALUE vsubkey = rb_class_new_instance(0, NULL, cGpgmeSubKey);
      rb_iv_set (vsubkey, "@revoked", INT2FIX(subkey->revoked));
      rb_iv_set (vsubkey, "@expired", INT2FIX(subkey->expired));
      rb_iv_set (vsubkey, "@disabled", INT2FIX(subkey->disabled));
      rb_iv_set (vsubkey, "@invalid", INT2FIX(subkey->invalid));
      rb_iv_set (vsubkey, "@can_encrypt", INT2FIX(subkey->can_encrypt));
      rb_iv_set (vsubkey, "@can_sign", INT2FIX(subkey->can_sign));
      rb_iv_set (vsubkey, "@can_certify", INT2FIX(subkey->can_certify));
      rb_iv_set (vsubkey, "@can_authenticate",
		 INT2FIX(subkey->can_authenticate));
      rb_iv_set (vsubkey, "@secret", INT2FIX(subkey->secret));
      rb_iv_set (vsubkey, "@pubkey_algo", INT2FIX(subkey->pubkey_algo));
      rb_iv_set (vsubkey, "@length", UINT2NUM(subkey->length));
      rb_iv_set (vsubkey, "@keyid", rb_str_new2 (subkey->keyid));
      rb_iv_set (vsubkey, "@fpr", rb_str_new2 (subkey->fpr));
      rb_iv_set (vsubkey, "@timestamp", LONG2NUM(subkey->timestamp));
      rb_iv_set (vsubkey, "@expires", LONG2NUM(subkey->expires));
      rb_ary_push (vsubkeys, vsubkey);
    }
  vuids = rb_ary_new ();
  rb_iv_set (vkey, "@uids", vuids);
  for (user_id = key->uids; user_id; user_id = user_id->next)
    {
      VALUE vuser_id = rb_class_new_instance(0, NULL, cGpgmeUserId),
	vsignatures = rb_ary_new ();
      rb_iv_set (vuser_id, "@revoked", INT2FIX(user_id->revoked));
      rb_iv_set (vuser_id, "@invalid", INT2FIX(user_id->invalid));
      rb_iv_set (vuser_id, "@validity", INT2FIX(user_id->validity));
      rb_iv_set (vuser_id, "@uid", rb_str_new2 (user_id->uid));
      rb_iv_set (vuser_id, "@name", rb_str_new2 (user_id->name));
      rb_iv_set (vuser_id, "@comment", rb_str_new2 (user_id->comment));
      rb_iv_set (vuser_id, "@email", rb_str_new2 (user_id->email));

      gpgme_key_sig_t key_sig;
      for (key_sig = user_id->signatures; key_sig; key_sig = key_sig->next)
	{
	  VALUE vkey_sig = rb_class_new_instance(0, NULL, cGpgmeKeySig);
	  rb_iv_set (vkey_sig, "@revoked", INT2FIX(key_sig->revoked));
	  rb_iv_set (vkey_sig, "@expired", INT2FIX(key_sig->expired));
	  rb_iv_set (vkey_sig, "@invalid", INT2FIX(key_sig->invalid));
	  rb_iv_set (vkey_sig, "@exportable", INT2FIX(key_sig->exportable));
	  rb_iv_set (vkey_sig, "@pubkey_algo", INT2FIX(key_sig->pubkey_algo));
	  rb_iv_set (vkey_sig, "@keyid", rb_str_new2 (key_sig->keyid));
	  rb_iv_set (vkey_sig, "@timestamp", LONG2NUM(key_sig->timestamp));
	  rb_iv_set (vkey_sig, "@expires", LONG2NUM(key_sig->expires));
	  rb_ary_push (vsignatures, vkey_sig);
	}
      rb_ary_push (vuids, vuser_id);
    }
  return vkey;
}

static VALUE
rb_s_gpgme_op_keylist_next (dummy, vctx, rkey)
     VALUE dummy, vctx, rkey;
{
  gpgme_ctx_t ctx;
  gpgme_key_t key;
  gpgme_error_t err;

  UNWRAP_GPGME_CTX(vctx, ctx);
  err = gpgme_op_keylist_next (ctx, &key);
  if (gpgme_err_code(err) == GPG_ERR_NO_ERROR)
    rb_ary_push (rkey, wrap_gpgme_key (key));
  return LONG2NUM(err);
}

static VALUE
rb_s_gpgme_op_keylist_end (dummy, vctx)
     VALUE dummy, vctx;
{
  gpgme_ctx_t ctx;
  gpgme_error_t err;

  UNWRAP_GPGME_CTX(vctx, ctx);
  err = gpgme_op_keylist_end (ctx);
  return LONG2NUM(err);
}

static VALUE
rb_s_gpgme_get_key (dummy, vctx, vfpr, rkey, vsecret)
     VALUE dummy, vctx, vfpr, rkey, vsecret;
{
  gpgme_ctx_t ctx;
  gpgme_error_t err;
  gpgme_key_t key;

  UNWRAP_GPGME_CTX(vctx, ctx);
  err = gpgme_get_key (ctx, StringValueCStr(vfpr), &key, NUM2INT(vsecret));

  if (gpgme_err_code(err) == GPG_ERR_NO_ERROR)
    rb_ary_push (rkey, wrap_gpgme_key (key));
  return LONG2NUM(err);
}

static VALUE
rb_s_gpgme_key_get_string_attr (dummy, vkey, vwhat, vidx)
     VALUE dummy, vkey, vwhat, vidx;
{
  gpgme_key_t key;
  const char *attr;

  UNWRAP_GPGME_KEY(vkey, key);
  attr = gpgme_key_get_string_attr (key, NUM2INT(vwhat), NULL, NUM2INT(vidx));
  if (!attr)
    return Qnil;
  return rb_str_new2 (attr);
}

static VALUE
rb_s_gpgme_key_get_ulong_attr (dummy, vkey, vwhat, vidx)
     VALUE dummy, vkey, vwhat, vidx;
{
  gpgme_key_t key;
  unsigned long attr;

  UNWRAP_GPGME_KEY(vkey, key);
  attr = gpgme_key_get_ulong_attr (key, NUM2INT(vwhat), NULL,
				   NUM2INT(vidx));
  return ULONG2NUM(attr);
}

static VALUE
rb_s_gpgme_key_ref (dummy, vkey)
     VALUE dummy, vkey;
{
  gpgme_key_t key;
  
  UNWRAP_GPGME_KEY(vkey, key);
  gpgme_key_ref (key);
  return Qnil;
}

static VALUE
rb_s_gpgme_key_unref (dummy, vkey)
     VALUE dummy, vkey;
{
  gpgme_key_t key;

  UNWRAP_GPGME_KEY(vkey, key);
  gpgme_key_unref (key);
  return Qnil;
}

static VALUE
rb_s_gpgme_op_genkey (dummy, vctx, vparms, vpubkey, vseckey)
     VALUE dummy, vctx, vparms, vpubkey, vseckey;
{
  gpgme_ctx_t ctx;
  gpgme_data_t pubkey = NULL, seckey = NULL;
  gpgme_error_t err;

  UNWRAP_GPGME_CTX(vctx, ctx);
  if (!NIL_P(vpubkey))
    UNWRAP_GPGME_DATA(vpubkey, pubkey);
  if (!NIL_P(vseckey))
    UNWRAP_GPGME_DATA(vseckey, seckey);
  err = gpgme_op_genkey (ctx, StringValueCStr(vparms), pubkey, seckey);
  return LONG2NUM(err);
}

static VALUE
rb_s_gpgme_op_genkey_start (dummy, vctx, vparms, vpubkey, vseckey)
     VALUE dummy, vctx, vparms, vpubkey, vseckey;
{
  gpgme_ctx_t ctx;
  gpgme_data_t pubkey = NULL, seckey = NULL;
  gpgme_error_t err;

  UNWRAP_GPGME_CTX(vctx, ctx);
  if (!NIL_P(vpubkey))
    UNWRAP_GPGME_DATA(vpubkey, pubkey);
  if (!NIL_P(vseckey))
    UNWRAP_GPGME_DATA(vseckey, seckey);
  err = gpgme_op_genkey_start (ctx, StringValueCStr(vparms), pubkey, seckey);
  return LONG2NUM(err);
}

static VALUE
rb_s_gpgme_op_export (dummy, vctx, vpattern, vreserved, vkeydata)
     VALUE dummy, vctx, vpattern, vreserved, vkeydata;
{
  gpgme_ctx_t ctx;
  gpgme_data_t keydata;
  gpgme_error_t err;

  UNWRAP_GPGME_CTX(vctx, ctx);
  UNWRAP_GPGME_DATA(vkeydata, keydata);

  err = gpgme_op_export (ctx, StringValueCStr(vpattern), NUM2UINT(vreserved),
			 keydata);
  return LONG2NUM(err);
}

static VALUE
rb_s_gpgme_op_export_start (dummy, vctx, vpattern, vreserved, vkeydata)
     VALUE dummy, vctx, vpattern, vreserved, vkeydata;
{
  gpgme_ctx_t ctx;
  gpgme_data_t keydata;
  gpgme_error_t err;

  UNWRAP_GPGME_CTX(vctx, ctx);
  UNWRAP_GPGME_DATA(vkeydata, keydata);

  err = gpgme_op_export_start (ctx, StringValueCStr(vpattern),
			       NUM2UINT(vreserved), keydata);
  return LONG2NUM(err);
}

static VALUE
rb_s_gpgme_op_import (dummy, vctx, vkeydata)
     VALUE dummy, vctx, vkeydata;
{
  gpgme_ctx_t ctx;
  gpgme_data_t keydata;
  gpgme_error_t err;

  UNWRAP_GPGME_CTX(vctx, ctx);
  UNWRAP_GPGME_DATA(vkeydata, keydata);

  err = gpgme_op_import (ctx, keydata);
  return LONG2NUM(err);
}

static VALUE
rb_s_gpgme_op_import_start (dummy, vctx, vkeydata)
     VALUE dummy, vctx, vkeydata;
{
  gpgme_ctx_t ctx;
  gpgme_data_t keydata;
  gpgme_error_t err;

  UNWRAP_GPGME_CTX(vctx, ctx);
  UNWRAP_GPGME_DATA(vkeydata, keydata);

  err = gpgme_op_import_start (ctx, keydata);
  return LONG2NUM(err);
}

static VALUE
rb_s_gpgme_op_import_ext (dummy, vctx, vkeydata, rnr)
     VALUE dummy, vctx, vkeydata, rnr;
{
  gpgme_ctx_t ctx;
  gpgme_data_t keydata;
  int nr, err;

  UNWRAP_GPGME_CTX(vctx, ctx);
  UNWRAP_GPGME_DATA(vkeydata, keydata);

  err = gpgme_op_import_ext (ctx, keydata, &nr);
  if (gpgme_err_code(err) == GPG_ERR_NO_ERROR)
    rb_ary_push (rnr, INT2NUM(nr));
  return LONG2NUM(err);
}

static VALUE
rb_s_gpgme_op_delete (dummy, vctx, vkey, vallow_secret)
     VALUE dummy, vctx, vkey, vallow_secret;
{
  gpgme_ctx_t ctx;
  gpgme_key_t key;
  gpgme_error_t err;

  UNWRAP_GPGME_CTX(vctx, ctx);
  UNWRAP_GPGME_KEY(vkey, key);

  err = gpgme_op_delete (ctx, key, NUM2INT(vallow_secret));
  return LONG2NUM(err);
}

static VALUE
rb_s_gpgme_op_delete_start (dummy, vctx, vkey, vallow_secret)
     VALUE dummy, vctx, vkey, vallow_secret;
{
  gpgme_ctx_t ctx;
  gpgme_key_t key;
  gpgme_error_t err;

  UNWRAP_GPGME_CTX(vctx, ctx);
  UNWRAP_GPGME_KEY(vkey, key);

  err = gpgme_op_delete_start (ctx, key, NUM2INT(vallow_secret));
  return LONG2NUM(err);
}

static VALUE
rb_s_gpgme_op_trustlist_start (dummy, vctx, vpattern, vmax_level)
     VALUE dummy, vctx, vpattern, vmax_level;
{
  gpgme_ctx_t ctx;
  gpgme_error_t err;

  UNWRAP_GPGME_CTX(vctx, ctx);
  err = gpgme_op_trustlist_start (ctx, StringValueCStr(vpattern),
				  NUM2INT(vmax_level));
  return LONG2NUM(err);
}

static VALUE
rb_s_gpgme_op_trustlist_next (dummy, vctx, ritem)
     VALUE dummy, vctx, ritem;
{
  gpgme_ctx_t ctx;
  gpgme_trust_item_t item;
  gpgme_error_t err;

  UNWRAP_GPGME_CTX(vctx, ctx);
  err = gpgme_op_trustlist_next (ctx, &item);
  if (gpgme_err_code(err) == GPG_ERR_NO_ERROR)
    rb_ary_push (ritem, WRAP_GPGME_TRUST_ITEM(item));
  return LONG2NUM(err);
}

static VALUE
rb_s_gpgme_op_trustlist_end (dummy, vctx)
     VALUE dummy, vctx;
{
  gpgme_ctx_t ctx;
  gpgme_error_t err;

  UNWRAP_GPGME_CTX(vctx, ctx);
  err = gpgme_op_trustlist_end (ctx);
  return LONG2NUM(err);
}

static VALUE
rb_s_gpgme_trust_item_get_string_attr (dummy, vitem, vwhat, vidx)
     VALUE dummy, vitem, vwhat, vidx;
{
  gpgme_trust_item_t item;
  const char *attr;

  UNWRAP_GPGME_TRUST_ITEM(vitem, item);
  attr = gpgme_trust_item_get_string_attr (item, NUM2INT(vwhat), NULL,
					   NUM2INT(vidx));
  if (!attr)
    return Qnil;
  return rb_str_new2 (attr);
}

static VALUE
rb_s_gpgme_trust_item_get_int_attr (dummy, vitem, vwhat, vidx)
     VALUE dummy, vitem, vwhat, vidx;
{
  gpgme_trust_item_t item;
  int attr;

  UNWRAP_GPGME_TRUST_ITEM(vitem, item);
  attr = gpgme_trust_item_get_int_attr (item, NUM2INT(vwhat), NULL,
					NUM2INT(vidx));
  return INT2NUM(attr);
}

static VALUE
rb_s_gpgme_trust_item_release (dummy, vitem)
     VALUE dummy, vitem;
{
  gpgme_trust_item_t item;

  UNWRAP_GPGME_TRUST_ITEM(vitem, item);
  if (!item)
    rb_raise (rb_eRuntimeError,
      "gpgme_trust_item_t has already been released.");
  gpgme_trust_item_release (item);
  DATA_PTR(vitem) = NULL;
  return Qnil;
}

static VALUE
rb_s_gpgme_op_decrypt (dummy, vctx, vcipher, vplain)
     VALUE dummy, vctx, vcipher, vplain;
{
  gpgme_ctx_t ctx;
  gpgme_data_t cipher, plain;
  gpgme_error_t err;

  UNWRAP_GPGME_CTX(vctx, ctx);
  UNWRAP_GPGME_DATA(vcipher, cipher);
  UNWRAP_GPGME_DATA(vplain, plain);

  err = gpgme_op_decrypt (ctx, cipher, plain);
  return LONG2NUM(err);
}

static VALUE
rb_s_gpgme_op_decrypt_start (dummy, vctx, vcipher, vplain)
     VALUE dummy, vctx, vcipher, vplain;
{
  gpgme_ctx_t ctx;
  gpgme_data_t cipher, plain;
  gpgme_error_t err;

  UNWRAP_GPGME_CTX(vctx, ctx);
  UNWRAP_GPGME_DATA(vcipher, cipher);
  UNWRAP_GPGME_DATA(vplain, plain);

  err = gpgme_op_decrypt_start (ctx, cipher, plain);
  return LONG2NUM(err);
}

static VALUE
rb_s_gpgme_op_verify (dummy, vctx, vsig, vsigned_text, vplain)
     VALUE dummy, vctx, vsig, vsigned_text, vplain;
{
  gpgme_ctx_t ctx;
  gpgme_data_t sig, signed_text = NULL, plain = NULL;
  gpgme_error_t err;

  UNWRAP_GPGME_CTX(vctx, ctx);
  UNWRAP_GPGME_DATA(vsig, sig);
  if (!NIL_P(vsigned_text))
    UNWRAP_GPGME_DATA(vsigned_text, signed_text);
  if (!NIL_P(vplain))
    UNWRAP_GPGME_DATA(vplain, plain);

  err = gpgme_op_verify (ctx, sig, signed_text, plain);
  return LONG2NUM(err);
}

static VALUE
rb_s_gpgme_op_verify_start (dummy, vctx, vsig, vsigned_text, vplain)
     VALUE dummy, vctx, vsig, vsigned_text, vplain;
{
  gpgme_ctx_t ctx;
  gpgme_data_t sig, signed_text, plain;
  gpgme_error_t err;

  UNWRAP_GPGME_CTX(vctx, ctx);
  UNWRAP_GPGME_DATA(vsig, sig);
  UNWRAP_GPGME_DATA(vsigned_text, signed_text);
  UNWRAP_GPGME_DATA(vplain, plain);

  err = gpgme_op_verify_start (ctx, sig, signed_text, plain);
  return LONG2NUM(err);
}

static VALUE
rb_s_gpgme_op_verify_result (dummy, vctx)
     VALUE dummy, vctx;
{
  gpgme_ctx_t ctx;
  gpgme_verify_result_t verify_result;
  gpgme_signature_t signature;
  VALUE vverify_result, vsignatures = rb_ary_new ();
  
  UNWRAP_GPGME_CTX(vctx, ctx);

  verify_result = gpgme_op_verify_result (ctx);
  vverify_result = rb_class_new_instance(0, NULL, cGpgmeVerifyResult);
  rb_iv_set (vverify_result, "@signatures", vsignatures);
  for (signature = verify_result->signatures; signature;
       signature = signature->next)
    {
      VALUE vsignature = rb_class_new_instance(0, NULL, cGpgmeSignature),
	vnotations = rb_ary_new ();
      gpgme_sig_notation_t notation;
      rb_iv_set (vsignature, "@summary", INT2FIX(signature->summary));
      rb_iv_set (vsignature, "@fpr", rb_str_new2 (signature->fpr));
      rb_iv_set (vsignature, "@status", LONG2NUM(signature->status));
      rb_iv_set (vsignature, "@notations", vnotations);
      for (notation = signature->notations; notation;
	   notation = notation->next)
	{
	  VALUE vnotation = rb_class_new_instance(0, NULL, cGpgmeSigNotation);
	  rb_iv_set (vnotation, "@name", rb_str_new2 (notation->name));
	  rb_iv_set (vnotation, "@value", rb_str_new2 (notation->value));
	  rb_ary_push (vnotations, vnotation);
	}
      rb_iv_set (vsignature, "@timestamp", ULONG2NUM(signature->timestamp));
      rb_iv_set (vsignature, "@exp_timestamp",
		 ULONG2NUM(signature->exp_timestamp));
      rb_iv_set (vsignature, "@wrong_key_usage",
		 INT2FIX(signature->wrong_key_usage));
      rb_iv_set (vsignature, "@validity", INT2FIX(signature->validity));
      rb_iv_set (vsignature, "@validity_reason",
		 LONG2NUM(signature->validity_reason));
      rb_ary_push (vsignatures, vsignature);
    }
  return vverify_result;
}

static VALUE
rb_s_gpgme_get_sig_status (dummy, vctx, vidx, rstat, rcreated)
     VALUE dummy, vctx, vidx, rstat, rcreated;
{
  gpgme_ctx_t ctx;
  gpgme_sig_stat_t stat;
  time_t created;
  const char *fingerprint;

  UNWRAP_GPGME_CTX(vctx, ctx);
  fingerprint = gpgme_get_sig_status (ctx, NUM2INT(vidx), &stat, &created);
  if (!fingerprint)
    return Qnil;
  rb_ary_push (rstat, INT2NUM(stat));
  rb_ary_push (rcreated, rb_time_new (created, 0));
  return rb_str_new2 (fingerprint);
}

static VALUE
rb_s_gpgme_get_sig_string_attr (dummy, vctx, vidx, vwhat, vwhatidx)
     VALUE dummy, vctx, vidx, vwhat, vwhatidx;
{
  gpgme_ctx_t ctx;
  const char *attr;

  UNWRAP_GPGME_CTX(vctx, ctx);
  attr = gpgme_get_sig_string_attr (ctx, NUM2INT(vidx), NUM2INT(vwhat),
				    NUM2INT(vwhatidx));
  if (!attr)
    return Qnil;
  return rb_str_new2 (attr);
}

static VALUE
rb_s_gpgme_get_sig_ulong_attr (dummy, vctx, vidx, vwhat, vwhatidx)
     VALUE dummy, vctx, vidx, vwhat, vwhatidx;
{
  gpgme_ctx_t ctx;
  unsigned long attr;

  UNWRAP_GPGME_CTX(vctx, ctx);
  attr = gpgme_get_sig_ulong_attr (ctx, NUM2INT(vidx), NUM2INT(vwhat),
				   NUM2INT(vwhatidx));
  return ULONG2NUM(attr);
}

static VALUE
rb_s_gpgme_get_sig_key (dummy, vctx, vidx, rkey)
     VALUE dummy, vctx, vidx, rkey;
{
  gpgme_ctx_t ctx;
  gpgme_key_t key;
  gpgme_error_t err;

  UNWRAP_GPGME_CTX(vctx, ctx);
  err = gpgme_get_sig_key (ctx, NUM2INT(vidx), &key);
  if (gpgme_err_code(err) == GPG_ERR_NO_ERROR)
    rb_ary_push (rkey, WRAP_GPGME_KEY(key));
  return LONG2NUM(err);
}

static VALUE
rb_s_gpgme_op_decrypt_verify (dummy, vctx, vcipher, vplain)
     VALUE dummy, vctx, vcipher, vplain;
{
  gpgme_ctx_t ctx;
  gpgme_data_t cipher, plain;
  gpgme_error_t err;

  UNWRAP_GPGME_CTX(vctx, ctx);
  UNWRAP_GPGME_DATA(vcipher, cipher);
  UNWRAP_GPGME_DATA(vplain, plain);

  err = gpgme_op_decrypt_verify (ctx, cipher, plain);
  return LONG2NUM(err);
}

static VALUE
rb_s_gpgme_op_decrypt_verify_start (dummy, vctx, vcipher, vplain)
     VALUE dummy, vctx, vcipher, vplain;
{
  gpgme_ctx_t ctx;
  gpgme_data_t cipher, plain;
  gpgme_error_t err;

  UNWRAP_GPGME_CTX(vctx, ctx);
  UNWRAP_GPGME_DATA(vcipher, cipher);
  UNWRAP_GPGME_DATA(vplain, plain);

  err = gpgme_op_decrypt_verify_start (ctx, cipher, plain);
  return LONG2NUM(err);
}

static VALUE
rb_s_gpgme_signers_clear (dummy, vctx)
     VALUE dummy, vctx;
{
  gpgme_ctx_t ctx;

  UNWRAP_GPGME_CTX(vctx, ctx);
  gpgme_signers_clear (ctx);
  return Qnil;
}

static VALUE
rb_s_gpgme_signers_add (dummy, vctx, vkey)
     VALUE dummy, vctx, vkey;
{
  gpgme_ctx_t ctx;
  gpgme_key_t key;
  gpgme_error_t err;

  UNWRAP_GPGME_CTX(vctx, ctx);
  UNWRAP_GPGME_KEY(vkey, key);

  err = gpgme_signers_add (ctx, key);
  return LONG2NUM(err);
}

static VALUE
rb_s_gpgme_signers_enum (dummy, vctx, vseq)
     VALUE dummy, vctx, vseq;
{
  gpgme_ctx_t ctx;
  gpgme_key_t key;

  UNWRAP_GPGME_CTX(vctx, ctx);

  key = gpgme_signers_enum (ctx, NUM2INT(vseq));
  if (!key)
    return Qnil;
  return WRAP_GPGME_KEY(key);
}

static VALUE
rb_s_gpgme_op_sign (dummy, vctx, vplain, vsig, vmode)
     VALUE dummy, vctx, vplain, vsig, vmode;
{
  gpgme_ctx_t ctx;
  gpgme_data_t plain, sig;
  gpgme_error_t err;

  UNWRAP_GPGME_CTX(vctx, ctx);
  UNWRAP_GPGME_DATA(vplain, plain);
  UNWRAP_GPGME_DATA(vsig, sig);

  err = gpgme_op_sign (ctx, plain, sig, NUM2INT(vmode));
  return LONG2NUM(err);
}

static VALUE
rb_s_gpgme_op_sign_start (dummy, vctx, vplain, vsig, vmode)
     VALUE dummy, vctx, vplain, vsig, vmode;
{
  gpgme_ctx_t ctx;
  gpgme_data_t plain, sig;
  gpgme_error_t err;

  UNWRAP_GPGME_CTX(vctx, ctx);
  UNWRAP_GPGME_DATA(vplain, plain);
  UNWRAP_GPGME_DATA(vsig, sig);

  err = gpgme_op_sign_start (ctx, plain, sig, NUM2INT(vmode));
  return LONG2NUM(err);
}

static VALUE
rb_s_gpgme_op_encrypt (dummy, vctx, vrecp, vflags, vplain, vcipher)
     VALUE dummy, vctx, vrecp, vflags, vplain, vcipher;
{
  gpgme_ctx_t ctx;
  gpgme_key_t *recp = NULL;
  gpgme_data_t plain, cipher;
  gpgme_error_t err;

  UNWRAP_GPGME_CTX(vctx, ctx);
  /* If RECP is `NULL', symmetric rather than public key encryption is
     performed. */
  if (!NIL_P(vrecp))
    {
      int i;
      recp = ALLOCA_N(gpgme_key_t, RARRAY_LEN(vrecp) + 1);
      for (i = 0; i < RARRAY_LEN(vrecp); i++)
	UNWRAP_GPGME_KEY(RARRAY_PTR(vrecp)[i], recp[i]);
      recp[i] = NULL;
    }
  UNWRAP_GPGME_DATA(vplain, plain);
  UNWRAP_GPGME_DATA(vcipher, cipher);

  err = gpgme_op_encrypt (ctx, recp, NUM2INT(vflags), plain, cipher);
  return LONG2NUM(err);
}

static VALUE
rb_s_gpgme_op_encrypt_start (dummy, vctx, vrecp, vflags, vplain, vcipher)
     VALUE dummy, vctx, vrecp, vflags, vplain, vcipher;
{
  gpgme_ctx_t ctx;
  gpgme_key_t *recp = NULL;
  gpgme_data_t plain, cipher;
  gpgme_error_t err;

  UNWRAP_GPGME_CTX(vctx, ctx);
  /* If RECP is `NULL', symmetric rather than public key encryption is
     performed. */
  if (!NIL_P(vrecp))
    {
      int i;
      recp = ALLOCA_N(gpgme_key_t, RARRAY_LEN(vrecp) + 1);
      for (i = 0; i < RARRAY_LEN(vrecp); i++)
	UNWRAP_GPGME_KEY(RARRAY_PTR(vrecp)[i], recp[i]);
      recp[i] = NULL;
    }
  UNWRAP_GPGME_DATA(vplain, plain);
  UNWRAP_GPGME_DATA(vcipher, cipher);

  err = gpgme_op_encrypt_start (ctx, recp, NUM2INT(vflags), plain, cipher);
  return LONG2NUM(err);
}

static VALUE
rb_s_gpgme_op_encrypt_sign (dummy, vctx, vrecp, vflags, vplain, vcipher)
     VALUE dummy, vctx, vrecp, vflags, vplain, vcipher;
{
  gpgme_ctx_t ctx;
  gpgme_key_t *recp = NULL;
  gpgme_data_t plain, cipher;
  gpgme_error_t err;

  UNWRAP_GPGME_CTX(vctx, ctx);
  /* If RECP is `NULL', symmetric rather than public key encryption is
     performed. */
  if (!NIL_P(vrecp))
    {
      int i;
      recp = ALLOCA_N(gpgme_key_t, RARRAY_LEN(vrecp) + 1);
      for (i = 0; i < RARRAY_LEN(vrecp); i++)
	UNWRAP_GPGME_KEY(RARRAY_PTR(vrecp)[i], recp[i]);
      recp[i] = NULL;
    }
  UNWRAP_GPGME_DATA(vplain, plain);
  UNWRAP_GPGME_DATA(vcipher, cipher);

  err = gpgme_op_encrypt_sign (ctx, recp, NUM2INT(vflags), plain, cipher);
  return LONG2NUM(err);
}

static VALUE
rb_s_gpgme_op_encrypt_sign_start (dummy, vctx, vrecp, vflags, vplain, vcipher)
     VALUE dummy, vctx, vrecp, vflags, vplain, vcipher;
{
  gpgme_ctx_t ctx;
  gpgme_key_t *recp = NULL;
  gpgme_data_t plain, cipher;
  gpgme_error_t err;

  UNWRAP_GPGME_CTX(vctx, ctx);
  /* If RECP is `NULL', symmetric rather than public key encryption is
     performed. */
  if (!NIL_P(vrecp))
    {
      int i;
      recp = ALLOCA_N(gpgme_key_t, RARRAY_LEN(vrecp) + 1);
      for (i = 0; i < RARRAY_LEN(vrecp); i++)
	UNWRAP_GPGME_KEY(RARRAY_PTR(vrecp)[i], recp[i]);
      recp[i] = NULL;
    }
  UNWRAP_GPGME_DATA(vplain, plain);
  UNWRAP_GPGME_DATA(vcipher, cipher);

  err = gpgme_op_encrypt_sign_start (ctx, recp, NUM2INT(vflags), plain, cipher);
  return LONG2NUM(err);
}

static VALUE
rb_s_gpgme_wait (dummy, vctx, rstatus, vhang)
     VALUE dummy, vctx, rstatus, vhang;
{
  gpgme_ctx_t ctx = NULL;
  gpgme_error_t status;

  /* The CTX argument can be `NULL'.  In that case, `gpgme_wait' waits
     for any context to complete its operation. */
  if (!NIL_P(vctx))
    UNWRAP_GPGME_CTX(vctx, ctx);

  ctx = gpgme_wait (ctx, &status, NUM2INT(vhang));
  rb_ary_push (rstatus, INT2NUM(status));

  return WRAP_GPGME_CTX(ctx);
}

void Init_gpgme_n ()
{
  VALUE mGPGME;

  mGPGME = rb_define_module ("GPGME");

  rb_define_module_function (mGPGME, "gpgme_check_version",
			     rb_s_gpgme_check_version, 1);
  rb_define_module_function (mGPGME, "gpgme_engine_check_version",
			     rb_s_gpgme_engine_check_version, 1);
  rb_define_module_function (mGPGME, "gpgme_get_engine_info",
			     rb_s_gpgme_get_engine_info, 1);

  rb_define_module_function (mGPGME, "gpgme_err_code",
			     rb_s_gpgme_err_code, 1);
  rb_define_module_function (mGPGME, "gpgme_err_source",
			     rb_s_gpgme_err_source, 1);
  rb_define_module_function (mGPGME, "gpgme_strerror",
			     rb_s_gpgme_strerror, 1);

  cGpgmeEngineInfo =
    rb_define_class_under (mGPGME, "GpgmeEngineInfo", rb_cObject);
  cGpgmeCtx =
    rb_define_class_under (mGPGME, "GpgmeCtx", rb_cObject);
  cGpgmeData =
    rb_define_class_under (mGPGME, "GpgmeData", rb_cObject);
  cGpgmeKey =
    rb_define_class_under (mGPGME, "GpgmeKey", rb_cObject);
  cGpgmeSubKey =
    rb_define_class_under (mGPGME, "GpgmeSubKey", rb_cObject);
  cGpgmeUserId =
    rb_define_class_under (mGPGME, "GpgmeUserId", rb_cObject);
  cGpgmeKeySig =
    rb_define_class_under (mGPGME, "GpgmeKeySig", rb_cObject);
  cGpgmeVerifyResult =
    rb_define_class_under (mGPGME, "GpgmeVerifyResult", rb_cObject);
  cGpgmeSignature =
    rb_define_class_under (mGPGME, "GpgmeSignature", rb_cObject);
  cGpgmeSigNotation =
    rb_define_class_under (mGPGME, "GpgmeSigNotation", rb_cObject);
  cGpgmeTrustItem =
    rb_define_class_under (mGPGME, "GpgmeTrustItem", rb_cObject);

  /* Creating Data Buffers
   *
   * gpgme_data_new_from_filepart is not currently supported.
   */
  rb_define_module_function (mGPGME, "gpgme_data_new",
			     rb_s_gpgme_data_new, 1);
  rb_define_module_function (mGPGME, "gpgme_data_new_from_mem",
			     rb_s_gpgme_data_new_from_mem, 4);
  rb_define_module_function (mGPGME, "gpgme_data_new_from_file",
			     rb_s_gpgme_data_new_from_file, 3);
  rb_define_module_function (mGPGME, "gpgme_data_new_from_fd",
			     rb_s_gpgme_data_new_from_fd, 2);
  rb_define_module_function (mGPGME, "gpgme_data_new_from_cbs",
			     rb_s_gpgme_data_new_from_cbs, 3);

  /* Destroying Data Buffers */
  rb_define_module_function (mGPGME, "gpgme_data_release",
			     rb_s_gpgme_data_release, 1);
  rb_define_module_function (mGPGME, "gpgme_data_release_and_get_mem",
			     rb_s_gpgme_data_release_and_get_mem, 2);

  /* Manipulating Data Buffers */
  rb_define_module_function (mGPGME, "gpgme_data_read",
			     rb_s_gpgme_data_read, 3);
  rb_define_module_function (mGPGME, "gpgme_data_seek",
			     rb_s_gpgme_data_seek, 3);
  rb_define_module_function (mGPGME, "gpgme_data_write",
			     rb_s_gpgme_data_write, 3);
  rb_define_module_function (mGPGME, "gpgme_data_get_encoding",
			     rb_s_gpgme_data_get_encoding, 1);
  rb_define_module_function (mGPGME, "gpgme_data_set_encoding",
			     rb_s_gpgme_data_set_encoding, 2);

  /* Creating Contexts */
  rb_define_module_function (mGPGME, "gpgme_new",
			     rb_s_gpgme_new, 1);

  /* Destroying Contexts */
  rb_define_module_function (mGPGME, "gpgme_release",
			     rb_s_gpgme_release, 2);

  /* Context Attributes */
  rb_define_module_function (mGPGME, "gpgme_set_protocol",
			     rb_s_gpgme_set_protocol, 2);
  rb_define_module_function (mGPGME, "gpgme_get_protocol",
			     rb_s_gpgme_get_protocol, 1);
  rb_define_module_function (mGPGME, "gpgme_set_armor",
			     rb_s_gpgme_set_armor, 2);
  rb_define_module_function (mGPGME, "gpgme_get_armor",
			     rb_s_gpgme_get_armor, 1);
  rb_define_module_function (mGPGME, "gpgme_set_textmode",
			     rb_s_gpgme_set_textmode, 2);
  rb_define_module_function (mGPGME, "gpgme_get_textmode",
			     rb_s_gpgme_get_textmode, 1);
  rb_define_module_function (mGPGME, "gpgme_set_include_certs",
			     rb_s_gpgme_set_include_certs, 2);
  rb_define_module_function (mGPGME, "gpgme_get_include_certs",
			     rb_s_gpgme_get_include_certs, 1);
  rb_define_module_function (mGPGME, "gpgme_set_keylist_mode",
			     rb_s_gpgme_set_keylist_mode, 2);
  rb_define_module_function (mGPGME, "gpgme_get_keylist_mode",
			     rb_s_gpgme_get_keylist_mode, 1);
  rb_define_module_function (mGPGME, "gpgme_set_passphrase_cb",
			     rb_s_gpgme_set_passphrase_cb, 3);
  rb_define_module_function (mGPGME, "gpgme_get_passphrase_cb",
			     rb_s_gpgme_get_passphrase_cb, 3);
  rb_define_module_function (mGPGME, "gpgme_set_progress_cb",
			     rb_s_gpgme_set_progress_cb, 3);
  rb_define_module_function (mGPGME, "gpgme_get_progress_cb",
			     rb_s_gpgme_get_progress_cb, 3);

  /* Key Management */
  rb_define_module_function (mGPGME, "gpgme_op_keylist_start",
			     rb_s_gpgme_op_keylist_start, 3);
  rb_define_module_function (mGPGME, "gpgme_op_keylist_ext_start",
			     rb_s_gpgme_op_keylist_ext_start, 4);
  rb_define_module_function (mGPGME, "gpgme_op_keylist_next",
			     rb_s_gpgme_op_keylist_next, 2);
  rb_define_module_function (mGPGME, "gpgme_op_keylist_end",
			     rb_s_gpgme_op_keylist_end, 1);
  rb_define_module_function (mGPGME, "gpgme_get_key",
			     rb_s_gpgme_get_key, 4);
  rb_define_module_function (mGPGME, "gpgme_key_get_string_attr",
			     rb_s_gpgme_key_get_string_attr, 3);
  rb_define_module_function (mGPGME, "gpgme_key_get_ulong_attr",
			     rb_s_gpgme_key_get_ulong_attr, 3);
  rb_define_module_function (mGPGME, "gpgme_key_ref",
			     rb_s_gpgme_key_ref, 1);
  rb_define_module_function (mGPGME, "gpgme_key_unref",
			     rb_s_gpgme_key_unref, 1);
  rb_define_module_function (mGPGME, "gpgme_op_genkey",
			     rb_s_gpgme_op_genkey, 4);
  rb_define_module_function (mGPGME, "gpgme_op_genkey_start",
			     rb_s_gpgme_op_genkey_start, 4);
  rb_define_module_function (mGPGME, "gpgme_op_export",
			     rb_s_gpgme_op_export, 3);
  rb_define_module_function (mGPGME, "gpgme_op_export_start",
			     rb_s_gpgme_op_export_start, 3);
  rb_define_module_function (mGPGME, "gpgme_op_import",
			     rb_s_gpgme_op_import, 2);
  rb_define_module_function (mGPGME, "gpgme_op_import_start",
			     rb_s_gpgme_op_import_start, 2);
  rb_define_module_function (mGPGME, "gpgme_op_import_ext",
			     rb_s_gpgme_op_import_ext, 3);
  rb_define_module_function (mGPGME, "gpgme_op_delete",
			     rb_s_gpgme_op_delete, 3);
  rb_define_module_function (mGPGME, "gpgme_op_delete_start",
			     rb_s_gpgme_op_delete_start, 3);

  /* Trust Item Management */
  rb_define_module_function (mGPGME, "gpgme_op_trustlist_start",
			     rb_s_gpgme_op_trustlist_start, 3);
  rb_define_module_function (mGPGME, "gpgme_op_trustlist_next",
			     rb_s_gpgme_op_trustlist_next, 2);
  rb_define_module_function (mGPGME, "gpgme_op_trustlist_end",
			     rb_s_gpgme_op_trustlist_end, 1);
  rb_define_module_function (mGPGME, "gpgme_trust_item_get_string_attr",
			     rb_s_gpgme_trust_item_get_string_attr, 3);
  rb_define_module_function (mGPGME, "gpgme_trust_item_get_int_attr",
			     rb_s_gpgme_trust_item_get_int_attr, 3);
  rb_define_module_function (mGPGME, "gpgme_trust_item_release",
			     rb_s_gpgme_trust_item_release, 1);

  /* Decrypt */
  rb_define_module_function (mGPGME, "gpgme_op_decrypt",
			     rb_s_gpgme_op_decrypt, 3);
  rb_define_module_function (mGPGME, "gpgme_op_decrypt_start",
			     rb_s_gpgme_op_decrypt_start, 3);

  /* Verify */
  rb_define_module_function (mGPGME, "gpgme_op_verify",
			     rb_s_gpgme_op_verify, 4);
  rb_define_module_function (mGPGME, "gpgme_op_verify_start",
			     rb_s_gpgme_op_verify_start, 4);
  rb_define_module_function (mGPGME, "gpgme_op_verify_result",
			     rb_s_gpgme_op_verify_result, 1);
  rb_define_module_function (mGPGME, "gpgme_get_sig_status",
			     rb_s_gpgme_get_sig_status, 4);
  rb_define_module_function (mGPGME, "gpgme_get_sig_string_attr",
			     rb_s_gpgme_get_sig_string_attr, 4);
  rb_define_module_function (mGPGME, "gpgme_get_sig_ulong_attr",
			     rb_s_gpgme_get_sig_ulong_attr, 4);
  rb_define_module_function (mGPGME, "gpgme_get_sig_key",
			     rb_s_gpgme_get_sig_key, 3);

  /* Decrypt and Verify */
  rb_define_module_function (mGPGME, "gpgme_op_decrypt_verify",
			     rb_s_gpgme_op_decrypt_verify, 3);
  rb_define_module_function (mGPGME, "gpgme_op_decrypt_verify_start",
			     rb_s_gpgme_op_decrypt_verify_start, 3);

  /* Sign */
  rb_define_module_function (mGPGME, "gpgme_signers_clear",
			     rb_s_gpgme_signers_clear, 1);
  rb_define_module_function (mGPGME, "gpgme_signers_add",
			     rb_s_gpgme_signers_add, 2);
  rb_define_module_function (mGPGME, "gpgme_signers_enum",
			     rb_s_gpgme_signers_enum, 2);
  rb_define_module_function (mGPGME, "gpgme_op_sign",
			     rb_s_gpgme_op_sign, 4);
  rb_define_module_function (mGPGME, "gpgme_op_sign_start",
			     rb_s_gpgme_op_sign_start, 4);

  /* Encrypt */
  rb_define_module_function (mGPGME, "gpgme_op_encrypt",
			     rb_s_gpgme_op_encrypt, 5);
  rb_define_module_function (mGPGME, "gpgme_op_encrypt_start",
			     rb_s_gpgme_op_encrypt_start, 5);
  rb_define_module_function (mGPGME, "gpgme_op_encrypt_sign",
			     rb_s_gpgme_op_encrypt_sign, 5);
  rb_define_module_function (mGPGME, "gpgme_op_encrypt_sign_start",
			     rb_s_gpgme_op_encrypt_sign_start, 5);

  /* Run Control */
  rb_define_module_function (mGPGME, "gpgme_wait",
			     rb_s_gpgme_wait, 3);

  /* gpgme_err_code_t */
  rb_define_const (mGPGME, "GPG_ERR_EOF",
		   INT2FIX(GPG_ERR_EOF));
  rb_define_const (mGPGME, "GPG_ERR_NO_ERROR",
		   INT2FIX(GPG_ERR_NO_ERROR));
  rb_define_const (mGPGME, "GPG_ERR_GENERAL",
		   INT2FIX(GPG_ERR_GENERAL));
  rb_define_const (mGPGME, "GPG_ERR_ENOMEM",
		   INT2FIX(GPG_ERR_ENOMEM));
  rb_define_const (mGPGME, "GPG_ERR_INV_VALUE",
		   INT2FIX(GPG_ERR_INV_VALUE));
  rb_define_const (mGPGME, "GPG_ERR_UNUSABLE_PUBKEY",
		   INT2FIX(GPG_ERR_UNUSABLE_PUBKEY));
  rb_define_const (mGPGME, "GPG_ERR_UNUSABLE_SECKEY",
		   INT2FIX(GPG_ERR_UNUSABLE_SECKEY));
  rb_define_const (mGPGME, "GPG_ERR_NO_DATA",
		   INT2FIX(GPG_ERR_NO_DATA));
  rb_define_const (mGPGME, "GPG_ERR_CONFLICT",
		   INT2FIX(GPG_ERR_CONFLICT));
  rb_define_const (mGPGME, "GPG_ERR_NOT_IMPLEMENTED",
		   INT2FIX(GPG_ERR_NOT_IMPLEMENTED));
  rb_define_const (mGPGME, "GPG_ERR_DECRYPT_FAILED",
		   INT2FIX(GPG_ERR_DECRYPT_FAILED));
  rb_define_const (mGPGME, "GPG_ERR_BAD_PASSPHRASE",
		   INT2FIX(GPG_ERR_BAD_PASSPHRASE));
  rb_define_const (mGPGME, "GPG_ERR_CANCELED",
		   INT2FIX(GPG_ERR_CANCELED));
  rb_define_const (mGPGME, "GPG_ERR_INV_ENGINE",
		   INT2FIX(GPG_ERR_INV_ENGINE));
  rb_define_const (mGPGME, "GPG_ERR_AMBIGUOUS_NAME",
		   INT2FIX(GPG_ERR_AMBIGUOUS_NAME));
  rb_define_const (mGPGME, "GPG_ERR_WRONG_KEY_USAGE",
		   INT2FIX(GPG_ERR_WRONG_KEY_USAGE));
  rb_define_const (mGPGME, "GPG_ERR_CERT_REVOKED",
		   INT2FIX(GPG_ERR_CERT_REVOKED));
  rb_define_const (mGPGME, "GPG_ERR_CERT_EXPIRED",
		   INT2FIX(GPG_ERR_CERT_EXPIRED));
  rb_define_const (mGPGME, "GPG_ERR_NO_CRL_KNOWN",
		   INT2FIX(GPG_ERR_NO_CRL_KNOWN));
  rb_define_const (mGPGME, "GPG_ERR_NO_POLICY_MATCH",
		   INT2FIX(GPG_ERR_NO_POLICY_MATCH));
  rb_define_const (mGPGME, "GPG_ERR_NO_SECKEY",
		   INT2FIX(GPG_ERR_NO_SECKEY));
  rb_define_const (mGPGME, "GPG_ERR_MISSING_CERT",
		   INT2FIX(GPG_ERR_MISSING_CERT));
  rb_define_const (mGPGME, "GPG_ERR_BAD_CERT_CHAIN",
		   INT2FIX(GPG_ERR_BAD_CERT_CHAIN));
  rb_define_const (mGPGME, "GPG_ERR_UNSUPPORTED_ALGORITHM",
		   INT2FIX(GPG_ERR_UNSUPPORTED_ALGORITHM));
  rb_define_const (mGPGME, "GPG_ERR_BAD_SIGNATURE",
		   INT2FIX(GPG_ERR_BAD_SIGNATURE));
  rb_define_const (mGPGME, "GPG_ERR_NO_PUBKEY",
		   INT2FIX(GPG_ERR_NO_PUBKEY));

  /* gpgme_err_source_t */
  rb_define_const (mGPGME, "GPG_ERR_SOURCE_UNKNOWN",
		   INT2FIX(GPG_ERR_SOURCE_UNKNOWN));
  rb_define_const (mGPGME, "GPG_ERR_SOURCE_GPGME",
		   INT2FIX(GPG_ERR_SOURCE_GPGME));
  rb_define_const (mGPGME, "GPG_ERR_SOURCE_GPG",
		   INT2FIX(GPG_ERR_SOURCE_GPG));
  rb_define_const (mGPGME, "GPG_ERR_SOURCE_GPGSM",
		   INT2FIX(GPG_ERR_SOURCE_GPGSM));
  rb_define_const (mGPGME, "GPG_ERR_SOURCE_GCRYPT",
		   INT2FIX(GPG_ERR_SOURCE_GCRYPT));
  rb_define_const (mGPGME, "GPG_ERR_SOURCE_GPGAGENT",
		   INT2FIX(GPG_ERR_SOURCE_GPGAGENT));
  rb_define_const (mGPGME, "GPG_ERR_SOURCE_PINENTRY",
		   INT2FIX(GPG_ERR_SOURCE_PINENTRY));
  rb_define_const (mGPGME, "GPG_ERR_SOURCE_SCD",
		   INT2FIX(GPG_ERR_SOURCE_SCD));
  rb_define_const (mGPGME, "GPG_ERR_SOURCE_KEYBOX",
		   INT2FIX(GPG_ERR_SOURCE_KEYBOX));
  rb_define_const (mGPGME, "GPG_ERR_SOURCE_USER_1",
		   INT2FIX(GPG_ERR_SOURCE_USER_1));
  rb_define_const (mGPGME, "GPG_ERR_SOURCE_USER_2",
		   INT2FIX(GPG_ERR_SOURCE_USER_2));
  rb_define_const (mGPGME, "GPG_ERR_SOURCE_USER_3",
		   INT2FIX(GPG_ERR_SOURCE_USER_3));
  rb_define_const (mGPGME, "GPG_ERR_SOURCE_USER_4",
		   INT2FIX(GPG_ERR_SOURCE_USER_4));

  /* gpgme_data_encoding_t */
  rb_define_const (mGPGME, "GPGME_DATA_ENCODING_NONE",
		   INT2FIX(GPGME_DATA_ENCODING_NONE));
  rb_define_const (mGPGME, "GPGME_DATA_ENCODING_BINARY",
		   INT2FIX(GPGME_DATA_ENCODING_BINARY));
  rb_define_const (mGPGME, "GPGME_DATA_ENCODING_BASE64",
		   INT2FIX(GPGME_DATA_ENCODING_BASE64));
  rb_define_const (mGPGME, "GPGME_DATA_ENCODING_ARMOR",
		   INT2FIX(GPGME_DATA_ENCODING_ARMOR));

  /* gpgme_sig_stat_t */
  rb_define_const (mGPGME, "GPGME_SIG_STAT_NONE",
		   INT2FIX(GPGME_SIG_STAT_NONE));
  rb_define_const (mGPGME, "GPGME_SIG_STAT_GOOD",
		   INT2FIX(GPGME_SIG_STAT_GOOD));
  rb_define_const (mGPGME, "GPGME_SIG_STAT_BAD",
		   INT2FIX(GPGME_SIG_STAT_BAD));
  rb_define_const (mGPGME, "GPGME_SIG_STAT_NOKEY",
		   INT2FIX(GPGME_SIG_STAT_NOKEY));
  rb_define_const (mGPGME, "GPGME_SIG_STAT_NOSIG",
		   INT2FIX(GPGME_SIG_STAT_NOSIG));
  rb_define_const (mGPGME, "GPGME_SIG_STAT_ERROR",
		   INT2FIX(GPGME_SIG_STAT_ERROR));
  rb_define_const (mGPGME, "GPGME_SIG_STAT_DIFF",
		   INT2FIX(GPGME_SIG_STAT_DIFF));
  rb_define_const (mGPGME, "GPGME_SIG_STAT_GOOD_EXP",
		   INT2FIX(GPGME_SIG_STAT_GOOD_EXP));
  rb_define_const (mGPGME, "GPGME_SIG_STAT_GOOD_EXPKEY",
		   INT2FIX(GPGME_SIG_STAT_GOOD_EXPKEY));

  /* gpgme_sigsum_t */
  rb_define_const (mGPGME, "GPGME_SIGSUM_VALID",
		   INT2FIX(GPGME_SIGSUM_VALID));
  rb_define_const (mGPGME, "GPGME_SIGSUM_GREEN",
		   INT2FIX(GPGME_SIGSUM_GREEN));
  rb_define_const (mGPGME, "GPGME_SIGSUM_RED",
		   INT2FIX(GPGME_SIGSUM_RED));
  rb_define_const (mGPGME, "GPGME_SIGSUM_KEY_REVOKED",
		   INT2FIX(GPGME_SIGSUM_KEY_REVOKED));
  rb_define_const (mGPGME, "GPGME_SIGSUM_KEY_EXPIRED",
		   INT2FIX(GPGME_SIGSUM_KEY_EXPIRED));
  rb_define_const (mGPGME, "GPGME_SIGSUM_SIG_EXPIRED",
		   INT2FIX(GPGME_SIGSUM_SIG_EXPIRED));
  rb_define_const (mGPGME, "GPGME_SIGSUM_KEY_MISSING",
		   INT2FIX(GPGME_SIGSUM_KEY_MISSING));
  rb_define_const (mGPGME, "GPGME_SIGSUM_CRL_MISSING",
		   INT2FIX(GPGME_SIGSUM_CRL_MISSING));
  rb_define_const (mGPGME, "GPGME_SIGSUM_CRL_TOO_OLD",
		   INT2FIX(GPGME_SIGSUM_CRL_TOO_OLD));
  rb_define_const (mGPGME, "GPGME_SIGSUM_BAD_POLICY",
		   INT2FIX(GPGME_SIGSUM_BAD_POLICY));
  rb_define_const (mGPGME, "GPGME_SIGSUM_SYS_ERROR",
		   INT2FIX(GPGME_SIGSUM_SYS_ERROR));

  /* gpgme_sig_mode_t */
  rb_define_const (mGPGME, "GPGME_SIG_MODE_NORMAL",
		   INT2FIX(GPGME_SIG_MODE_NORMAL));
  rb_define_const (mGPGME, "GPGME_SIG_MODE_DETACH",
		   INT2FIX(GPGME_SIG_MODE_DETACH));
  rb_define_const (mGPGME, "GPGME_SIG_MODE_CLEAR",
		   INT2FIX(GPGME_SIG_MODE_CLEAR));

  /* gpgme_attr_t */
  rb_define_const (mGPGME, "GPGME_ATTR_KEYID",
		   INT2FIX(GPGME_ATTR_KEYID));
  rb_define_const (mGPGME, "GPGME_ATTR_FPR",
		   INT2FIX(GPGME_ATTR_FPR));
  rb_define_const (mGPGME, "GPGME_ATTR_ALGO",
		   INT2FIX(GPGME_ATTR_ALGO));
  rb_define_const (mGPGME, "GPGME_ATTR_LEN",
		   INT2FIX(GPGME_ATTR_LEN));
  rb_define_const (mGPGME, "GPGME_ATTR_CREATED",
		   INT2FIX(GPGME_ATTR_CREATED));
  rb_define_const (mGPGME, "GPGME_ATTR_EXPIRE",
		   INT2FIX(GPGME_ATTR_EXPIRE));
  rb_define_const (mGPGME, "GPGME_ATTR_OTRUST",
		   INT2FIX(GPGME_ATTR_OTRUST));
  rb_define_const (mGPGME, "GPGME_ATTR_USERID",
		   INT2FIX(GPGME_ATTR_USERID));
  rb_define_const (mGPGME, "GPGME_ATTR_NAME",
		   INT2FIX(GPGME_ATTR_NAME));
  rb_define_const (mGPGME, "GPGME_ATTR_EMAIL",
		   INT2FIX(GPGME_ATTR_EMAIL));
  rb_define_const (mGPGME, "GPGME_ATTR_COMMENT",
		   INT2FIX(GPGME_ATTR_COMMENT));
  rb_define_const (mGPGME, "GPGME_ATTR_VALIDITY",
		   INT2FIX(GPGME_ATTR_VALIDITY));
  rb_define_const (mGPGME, "GPGME_ATTR_LEVEL",
		   INT2FIX(GPGME_ATTR_LEVEL));
  rb_define_const (mGPGME, "GPGME_ATTR_TYPE",
		   INT2FIX(GPGME_ATTR_TYPE));
  rb_define_const (mGPGME, "GPGME_ATTR_IS_SECRET",
		   INT2FIX(GPGME_ATTR_IS_SECRET));
  rb_define_const (mGPGME, "GPGME_ATTR_KEY_REVOKED",
		   INT2FIX(GPGME_ATTR_KEY_REVOKED));
  rb_define_const (mGPGME, "GPGME_ATTR_KEY_INVALID",
		   INT2FIX(GPGME_ATTR_KEY_INVALID));
  rb_define_const (mGPGME, "GPGME_ATTR_UID_REVOKED",
		   INT2FIX(GPGME_ATTR_UID_REVOKED));
  rb_define_const (mGPGME, "GPGME_ATTR_UID_INVALID",
		   INT2FIX(GPGME_ATTR_UID_INVALID));
  rb_define_const (mGPGME, "GPGME_ATTR_KEY_CAPS",
		   INT2FIX(GPGME_ATTR_KEY_CAPS));
  rb_define_const (mGPGME, "GPGME_ATTR_CAN_ENCRYPT",
		   INT2FIX(GPGME_ATTR_CAN_ENCRYPT));
  rb_define_const (mGPGME, "GPGME_ATTR_CAN_SIGN",
		   INT2FIX(GPGME_ATTR_CAN_SIGN));
  rb_define_const (mGPGME, "GPGME_ATTR_CAN_CERTIFY",
		   INT2FIX(GPGME_ATTR_CAN_CERTIFY));
  rb_define_const (mGPGME, "GPGME_ATTR_KEY_EXPIRED",
		   INT2FIX(GPGME_ATTR_KEY_EXPIRED));
  rb_define_const (mGPGME, "GPGME_ATTR_KEY_DISABLED",
		   INT2FIX(GPGME_ATTR_KEY_DISABLED));
  rb_define_const (mGPGME, "GPGME_ATTR_SERIAL",
		   INT2FIX(GPGME_ATTR_SERIAL));
  rb_define_const (mGPGME, "GPGME_ATTR_ISSUER",
		   INT2FIX(GPGME_ATTR_ISSUER));
  rb_define_const (mGPGME, "GPGME_ATTR_CHAINID",
		   INT2FIX(GPGME_ATTR_CHAINID));
  rb_define_const (mGPGME, "GPGME_ATTR_SIG_STATUS",
		   INT2FIX(GPGME_ATTR_SIG_STATUS));
  rb_define_const (mGPGME, "GPGME_ATTR_ERRTOK",
		   INT2FIX(GPGME_ATTR_ERRTOK));
  rb_define_const (mGPGME, "GPGME_ATTR_SIG_SUMMARY",
		   INT2FIX(GPGME_ATTR_SIG_SUMMARY));

  /* gpgme_validity_t */
  rb_define_const (mGPGME, "GPGME_VALIDITY_UNKNOWN",
		   INT2FIX(GPGME_VALIDITY_UNKNOWN));
  rb_define_const (mGPGME, "GPGME_VALIDITY_UNDEFINED",
		   INT2FIX(GPGME_VALIDITY_UNDEFINED));
  rb_define_const (mGPGME, "GPGME_VALIDITY_NEVER",
		   INT2FIX(GPGME_VALIDITY_NEVER));
  rb_define_const (mGPGME, "GPGME_VALIDITY_MARGINAL",
		   INT2FIX(GPGME_VALIDITY_MARGINAL));
  rb_define_const (mGPGME, "GPGME_VALIDITY_FULL",
		   INT2FIX(GPGME_VALIDITY_FULL));
  rb_define_const (mGPGME, "GPGME_VALIDITY_ULTIMATE",
		   INT2FIX(GPGME_VALIDITY_ULTIMATE));

  /* gpgme_protocol_t */
  rb_define_const (mGPGME, "GPGME_PROTOCOL_OpenPGP",
		   INT2FIX(GPGME_PROTOCOL_OpenPGP));
  rb_define_const (mGPGME, "GPGME_PROTOCOL_CMS",
		   INT2FIX(GPGME_PROTOCOL_CMS));

  /* gpgme_status_code_t */
  rb_define_const (mGPGME, "GPGME_STATUS_EOF",
		   INT2FIX(GPGME_STATUS_EOF));
  /* mkstatus starts here */
  rb_define_const (mGPGME, "GPGME_STATUS_ENTER",
		   INT2FIX(GPGME_STATUS_ENTER));
  rb_define_const (mGPGME, "GPGME_STATUS_LEAVE",
		   INT2FIX(GPGME_STATUS_LEAVE));
  rb_define_const (mGPGME, "GPGME_STATUS_ABORT",
		   INT2FIX(GPGME_STATUS_ABORT));

  rb_define_const (mGPGME, "GPGME_STATUS_GOODSIG",
		   INT2FIX(GPGME_STATUS_GOODSIG));
  rb_define_const (mGPGME, "GPGME_STATUS_BADSIG",
		   INT2FIX(GPGME_STATUS_BADSIG));
  rb_define_const (mGPGME, "GPGME_STATUS_ERRSIG",
		   INT2FIX(GPGME_STATUS_ERRSIG));

  rb_define_const (mGPGME, "GPGME_STATUS_BADARMOR",
		   INT2FIX(GPGME_STATUS_BADARMOR));

  rb_define_const (mGPGME, "GPGME_STATUS_RSA_OR_IDEA",
		   INT2FIX(GPGME_STATUS_RSA_OR_IDEA));
  rb_define_const (mGPGME, "GPGME_STATUS_KEYEXPIRED",
		   INT2FIX(GPGME_STATUS_KEYEXPIRED));
  rb_define_const (mGPGME, "GPGME_STATUS_KEYREVOKED",
		   INT2FIX(GPGME_STATUS_KEYREVOKED));

  rb_define_const (mGPGME, "GPGME_STATUS_TRUST_UNDEFINED",
		   INT2FIX(GPGME_STATUS_TRUST_UNDEFINED));
  rb_define_const (mGPGME, "GPGME_STATUS_TRUST_NEVER",
		   INT2FIX(GPGME_STATUS_TRUST_NEVER));
  rb_define_const (mGPGME, "GPGME_STATUS_TRUST_MARGINAL",
		   INT2FIX(GPGME_STATUS_TRUST_MARGINAL));
  rb_define_const (mGPGME, "GPGME_STATUS_TRUST_FULLY",
		   INT2FIX(GPGME_STATUS_TRUST_FULLY));
  rb_define_const (mGPGME, "GPGME_STATUS_TRUST_ULTIMATE",
		   INT2FIX(GPGME_STATUS_TRUST_ULTIMATE));

  rb_define_const (mGPGME, "GPGME_STATUS_SHM_INFO",
		   INT2FIX(GPGME_STATUS_SHM_INFO));
  rb_define_const (mGPGME, "GPGME_STATUS_SHM_GET",
		   INT2FIX(GPGME_STATUS_SHM_GET));
  rb_define_const (mGPGME, "GPGME_STATUS_SHM_GET_BOOL",
		   INT2FIX(GPGME_STATUS_SHM_GET_BOOL));
  rb_define_const (mGPGME, "GPGME_STATUS_SHM_GET_HIDDEN",
		   INT2FIX(GPGME_STATUS_SHM_GET_HIDDEN));

  rb_define_const (mGPGME, "GPGME_STATUS_NEED_PASSPHRASE",
		   INT2FIX(GPGME_STATUS_NEED_PASSPHRASE));
  rb_define_const (mGPGME, "GPGME_STATUS_VALIDSIG",
		   INT2FIX(GPGME_STATUS_VALIDSIG));
  rb_define_const (mGPGME, "GPGME_STATUS_SIG_ID",
		   INT2FIX(GPGME_STATUS_SIG_ID));
  rb_define_const (mGPGME, "GPGME_STATUS_ENC_TO",
		   INT2FIX(GPGME_STATUS_ENC_TO));
  rb_define_const (mGPGME, "GPGME_STATUS_NODATA",
		   INT2FIX(GPGME_STATUS_NODATA));
  rb_define_const (mGPGME, "GPGME_STATUS_BAD_PASSPHRASE",
		   INT2FIX(GPGME_STATUS_BAD_PASSPHRASE));
  rb_define_const (mGPGME, "GPGME_STATUS_NO_PUBKEY",
		   INT2FIX(GPGME_STATUS_NO_PUBKEY));
  rb_define_const (mGPGME, "GPGME_STATUS_NO_SECKEY",
		   INT2FIX(GPGME_STATUS_NO_SECKEY));
  rb_define_const (mGPGME, "GPGME_STATUS_NEED_PASSPHRASE_SYM",
		   INT2FIX(GPGME_STATUS_NEED_PASSPHRASE_SYM));
  rb_define_const (mGPGME, "GPGME_STATUS_DECRYPTION_FAILED",
		   INT2FIX(GPGME_STATUS_DECRYPTION_FAILED));
  rb_define_const (mGPGME, "GPGME_STATUS_DECRYPTION_OKAY",
		   INT2FIX(GPGME_STATUS_DECRYPTION_OKAY));
  rb_define_const (mGPGME, "GPGME_STATUS_MISSING_PASSPHRASE",
		   INT2FIX(GPGME_STATUS_MISSING_PASSPHRASE));
  rb_define_const (mGPGME, "GPGME_STATUS_GOOD_PASSPHRASE",
		   INT2FIX(GPGME_STATUS_GOOD_PASSPHRASE));
  rb_define_const (mGPGME, "GPGME_STATUS_GOODMDC",
		   INT2FIX(GPGME_STATUS_GOODMDC));
  rb_define_const (mGPGME, "GPGME_STATUS_BADMDC",
		   INT2FIX(GPGME_STATUS_BADMDC));
  rb_define_const (mGPGME, "GPGME_STATUS_ERRMDC",
		   INT2FIX(GPGME_STATUS_ERRMDC));
  rb_define_const (mGPGME, "GPGME_STATUS_IMPORTED",
		   INT2FIX(GPGME_STATUS_IMPORTED));
  rb_define_const (mGPGME, "GPGME_STATUS_IMPORT_RES",
		   INT2FIX(GPGME_STATUS_IMPORT_RES));
  rb_define_const (mGPGME, "GPGME_STATUS_FILE_START",
		   INT2FIX(GPGME_STATUS_FILE_START));
  rb_define_const (mGPGME, "GPGME_STATUS_FILE_DONE",
		   INT2FIX(GPGME_STATUS_FILE_DONE));
  rb_define_const (mGPGME, "GPGME_STATUS_FILE_ERROR",
		   INT2FIX(GPGME_STATUS_FILE_ERROR));

  rb_define_const (mGPGME, "GPGME_STATUS_BEGIN_DECRYPTION",
		   INT2FIX(GPGME_STATUS_BEGIN_DECRYPTION));
  rb_define_const (mGPGME, "GPGME_STATUS_END_DECRYPTION",
		   INT2FIX(GPGME_STATUS_END_DECRYPTION));
  rb_define_const (mGPGME, "GPGME_STATUS_BEGIN_ENCRYPTION",
		   INT2FIX(GPGME_STATUS_BEGIN_ENCRYPTION));
  rb_define_const (mGPGME, "GPGME_STATUS_END_ENCRYPTION",
		   INT2FIX(GPGME_STATUS_END_ENCRYPTION));

  rb_define_const (mGPGME, "GPGME_STATUS_DELETE_PROBLEM",
		   INT2FIX(GPGME_STATUS_DELETE_PROBLEM));
  rb_define_const (mGPGME, "GPGME_STATUS_GET_BOOL",
		   INT2FIX(GPGME_STATUS_GET_BOOL));
  rb_define_const (mGPGME, "GPGME_STATUS_GET_LINE",
		   INT2FIX(GPGME_STATUS_GET_LINE));
  rb_define_const (mGPGME, "GPGME_STATUS_GET_HIDDEN",
		   INT2FIX(GPGME_STATUS_GET_HIDDEN));
  rb_define_const (mGPGME, "GPGME_STATUS_GOT_IT",
		   INT2FIX(GPGME_STATUS_GOT_IT));
  rb_define_const (mGPGME, "GPGME_STATUS_PROGRESS",
		   INT2FIX(GPGME_STATUS_PROGRESS));
  rb_define_const (mGPGME, "GPGME_STATUS_SIG_CREATED",
		   INT2FIX(GPGME_STATUS_SIG_CREATED));
  rb_define_const (mGPGME, "GPGME_STATUS_SESSION_KEY",
		   INT2FIX(GPGME_STATUS_SESSION_KEY));
  rb_define_const (mGPGME, "GPGME_STATUS_NOTATION_NAME",
		   INT2FIX(GPGME_STATUS_NOTATION_NAME));
  rb_define_const (mGPGME, "GPGME_STATUS_NOTATION_DATA",
		   INT2FIX(GPGME_STATUS_NOTATION_DATA));
  rb_define_const (mGPGME, "GPGME_STATUS_POLICY_URL",
		   INT2FIX(GPGME_STATUS_POLICY_URL));
  rb_define_const (mGPGME, "GPGME_STATUS_BEGIN_STREAM",
		   INT2FIX(GPGME_STATUS_BEGIN_STREAM));
  rb_define_const (mGPGME, "GPGME_STATUS_END_STREAM",
		   INT2FIX(GPGME_STATUS_END_STREAM));
  rb_define_const (mGPGME, "GPGME_STATUS_KEY_CREATED",
		   INT2FIX(GPGME_STATUS_KEY_CREATED));
  rb_define_const (mGPGME, "GPGME_STATUS_USERID_HINT",
		   INT2FIX(GPGME_STATUS_USERID_HINT));
  rb_define_const (mGPGME, "GPGME_STATUS_UNEXPECTED",
		   INT2FIX(GPGME_STATUS_UNEXPECTED));
  rb_define_const (mGPGME, "GPGME_STATUS_INV_RECP",
		   INT2FIX(GPGME_STATUS_INV_RECP));
  rb_define_const (mGPGME, "GPGME_STATUS_NO_RECP",
		   INT2FIX(GPGME_STATUS_NO_RECP));
  rb_define_const (mGPGME, "GPGME_STATUS_ALREADY_SIGNED",
		   INT2FIX(GPGME_STATUS_ALREADY_SIGNED));
  rb_define_const (mGPGME, "GPGME_STATUS_SIGEXPIRED",
		   INT2FIX(GPGME_STATUS_SIGEXPIRED));
  rb_define_const (mGPGME, "GPGME_STATUS_EXPSIG",
		   INT2FIX(GPGME_STATUS_EXPSIG));
  rb_define_const (mGPGME, "GPGME_STATUS_EXPKEYSIG",
		   INT2FIX(GPGME_STATUS_EXPKEYSIG));
  rb_define_const (mGPGME, "GPGME_STATUS_TRUNCATED",
		   INT2FIX(GPGME_STATUS_TRUNCATED));
  rb_define_const (mGPGME, "GPGME_STATUS_ERROR",
		   INT2FIX(GPGME_STATUS_ERROR));

  /* The available keylist mode flags.  */
  rb_define_const (mGPGME, "GPGME_KEYLIST_MODE_LOCAL",
		   INT2FIX(GPGME_KEYLIST_MODE_LOCAL));
  rb_define_const (mGPGME, "GPGME_KEYLIST_MODE_EXTERN",
		   INT2FIX(GPGME_KEYLIST_MODE_EXTERN));
  rb_define_const (mGPGME, "GPGME_KEYLIST_MODE_SIGS",
		   INT2FIX(GPGME_KEYLIST_MODE_SIGS));
}