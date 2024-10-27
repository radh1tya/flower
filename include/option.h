#ifndef FLOWER_OPTION_H
#define FLOWER_OPTION_H
#ifdef __cplusplus
extern "C" {
#endif

/* 
  * Option list, bisa ditambah yang lain dengan char utama
  * macro harus literal atau bisa terdeteksi saat waktu
  * kompilasi
  *
  * @NEXT_FEATURES
  * bisa ditambahkan 'b' untuk build atau yang lain
  */
#define OPTION_LIST "hv"

// Invalid option, seperti yang di set dari getopt_long
#define OPTION_INVALID -1

// -h atau --help
#define OPTION_HELP 'h'
// -v atau --version
#define OPTION_VERSION 'v'

#ifdef __cplusplus
}
#endif
#endif
