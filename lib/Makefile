CFLAGS=-Wno-builtin-declaration-mismatch
BITS=64   # change during make
LANG=NONE # change during make

lc = $(subst A,a,$(subst B,b,$(subst C,c,$(subst D,d,$(subst E,e,$(subst F,f,$(subst G,g,$(subst H,h,$(subst I,i,$(subst J,j,$(subst K,k,$(subst L,l,$(subst M,m,$(subst N,n,$(subst O,o,$(subst P,p,$(subst Q,q,$(subst R,r,$(subst S,s,$(subst T,t,$(subst U,u,$(subst V,v,$(subst W,w,$(subst X,x,$(subst Y,y,$(subst Z,z,$1))))))))))))))))))))))))))

.PHONY: lib
lib: lib.c
	$(CC) $(CFLAGS) -DBITS=$(BITS) -D$(LANG) lib.c -S -o ../$(call lc,$(LANG))/lib.s
