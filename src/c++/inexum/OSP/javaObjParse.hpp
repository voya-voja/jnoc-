#ifndef BISON_JAVAOBJPARSE_HPP
# define BISON_JAVAOBJPARSE_HPP

#ifndef YYSTYPE
typedef union{
	bool					Boolean;
	wchar_t					Char;
	short					Short;
	int						Int;
	inexum::JLong			Long;
	float					Float;
	double					Double;
	char*					String;
	long double				LongDouble;
	byte					Byte;
	unsigned				Unsigned;
	inexum::UnsignedJLong	UnsignedLong;
	inexum::OSP::Class*		ClassPtr;
} yystype;
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif
# define	TC_NULL	257
# define	TC_REFERENCE	258
# define	TC_CLASSDESC	259
# define	TC_OBJECT	260
# define	TC_STRING	261
# define	TC_ARRAY	262
# define	TC_CLASS	263
# define	TC_BLOCKDATA	264
# define	TC_ENDBLOCKDATA	265
# define	TC_RESET	266
# define	TC_BLOCKDATALONG	267
# define	TC_EXCEPTION	268
# define	VALUE_END	269
# define	BYTES_END	270
# define	ARRAY_END	271
# define	OBJECT_ANNOTATION	272
# define	OBJECT_END	273
# define	NOWRCLASS	274
# define	WRCLASS	275
# define	EXTERNAL_CONTENTS	276
# define	OBJECT_ANNOTATIONS	277
# define	BOOLEAN	278
# define	SHORT	279
# define	INT	280
# define	LONG	281
# define	BYTE	282
# define	STRING	283
# define	CHAR	284
# define	FLOAT	285
# define	DOUBLE	286


extern YYSTYPE yylval;

#endif /* not BISON_JAVAOBJPARSE_HPP */
