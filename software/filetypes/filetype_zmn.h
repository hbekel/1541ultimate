#ifndef FILETYPE_ZMACHINE_H
#define FILETYPE_ZMACHINE_H

#include "filetypes.h"
#include "browsable_root.h"

class SubsysCommand;

class FileTypeZMachine : public FileType
{
	BrowsableDirEntry *node;
    static int execute_st(SubsysCommand *);
    static int run(SubsysCommand *);
    static int view(SubsysCommand *);
    
    static uint8_t sys3[14];
    static uint8_t sys4[14];
    static uint8_t sys5[14];

    static void color3(uint8_t *prg, uint8_t fg, uint8_t bg, uint8_t st, uint8_t mr);
    static void color4(uint8_t *prg, uint8_t fg, uint8_t bg, uint8_t st, uint8_t mr);
    static void color5(uint8_t *prg, uint8_t fg, uint8_t bg, uint8_t st, uint8_t mr);    
    static uint8_t color2petscii[16];
    
    static uint8_t i3[0x2000];
    static uint8_t i4[0x2A00];
    static uint8_t i5[0x2F00];    
 public:
    FileTypeZMachine(BrowsableDirEntry *n);
    ~FileTypeZMachine();

    int fetch_context_items(IndexedList<Action *> &list);
    static FileType *test_type(BrowsableDirEntry *obj);
};

#endif // FILETYPE_ZMACHINE_H



