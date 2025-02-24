/* Copyright (C) 2024 John Törnblom

This program is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 3, or (at your option) any
later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; see the file COPYING. If not, see
<http://www.gnu.org/licenses/>.  */

#pragma once


/**
 * dynamic library loaded in kernel memory.
 **/
typedef struct dynlib_dynsec {
  struct {
    unsigned long le_next;
    unsigned long le_prev;
  } list_entry;

  unsigned long sysvec;
  unsigned int refcount;
  unsigned long size;

  unsigned long symtab;
  unsigned long symtabsize;

  unsigned long strtab;
  unsigned long strtabsize;

  unsigned long pltrela;
  unsigned long pltrelasize;

  unsigned long rela;
  unsigned long relasize;

  unsigned long hash;
  unsigned long hashsize;

  unsigned long dynamic;
  unsigned long dynamicsize;

  unsigned long sce_comment;
  unsigned long sce_commentsize;

  unsigned long sce_dynlib;
  unsigned long sce_dynlibsize;

  unsigned long unknown1;     // execpath?
  unsigned long unknown1size;

  unsigned long buckets;
  unsigned long bucketssize;
  unsigned int nbuckets;

  unsigned long chains;
  unsigned long chainssize;
  unsigned int nchains;

  unsigned long unknown2[7];
} dynlib_dynsec_t;


/**
 * an ELF loaded in kernel memory.
 **/
typedef struct dynlib_obj {
  unsigned long next;
  unsigned long path;
  unsigned long unknown0[2];
  unsigned int refcount;
  unsigned long handle;

  unsigned long mapbase;
  unsigned long mapsize;
  unsigned long textsize;

  unsigned long database;
  unsigned long datasize;

  unsigned long unknown1;
  unsigned long unknown1size;

  unsigned long entry;
  unsigned long unknown2;
  unsigned long vaddrbase;

  unsigned int tlsindex;
  unsigned long tlsinit;
  unsigned long tlsinitsize;
  unsigned long tlssize;
  unsigned long  tlsoffset;
  unsigned long tlsalign;

  unsigned long pltgot;

  unsigned long unknown3[6];

  unsigned long init;
  unsigned long fini;

  unsigned long eh_frame_hdr;
  unsigned long eh_frame_hdr_size;

  unsigned long eh_frame;
  unsigned long eh_frame_size;

  int status;
  int flags;

  unsigned long unknown4[5];
  unsigned long dynsec;
  unsigned long unknown5[6]; //fingerprint?
} dynlib_obj_t;


int kernel_copyout(unsigned long kaddr, void *uaddr, unsigned long len);

unsigned long kernel_get_ucred_authid(int pid);
int           kernel_set_ucred_authid(int pid, unsigned long authid);

unsigned long kernel_get_ucred_attrs(int pid);
int           kernel_set_ucred_attrs(int pid, unsigned long attrs);

int kernel_get_ucred_caps(int pid, unsigned char caps[16]);
int kernel_set_ucred_caps(int pid, const unsigned char caps[16]);

unsigned long kernel_get_root_vnode(void);
unsigned long kernel_get_proc_rootdir(int pid);
int           kernel_set_proc_rootdir(int pid, unsigned long vnode);

int kernel_dynlib_obj(int pid, unsigned int handle, dynlib_obj_t* obj);
int kernel_dynlib_handle(int pid, const char* basename, unsigned int *handle);

unsigned long kernel_dynlib_dlsym(int pid, unsigned int handle, const char* sym);
