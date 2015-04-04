source .vim/vimrc.basic

au VimLeave * :mksession! .vim/session.c
if getfsize(".vim/session.c") >= 0
    source .vim/session.c
endif

"add mappings
map <F4> :execute "vimgrep /" . expand("<cword>") . "/j **/*.cc **/*.h" <Bar> cw<CR>
map <F8> :vertical wincmd f<CR>
set makeprg=cmake\ .\ &&\ make
nnoremap <F9> :make!<cr>
