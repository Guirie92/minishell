# Requirements (possibly not needed)

Linux: 
```
sudo apt install libreadline-dev
```

macOS: 
```
brew install readline
```
# Disclaimer:
I made this project solo from scratch in roughly a month. I tried to keep the
project modular and organized, but due to time constraints, I believe there
are still a few areas were code duplication could've been avoided, or areas that
could've been modularized. That said, if time allows it, I'll be improving it
overtime, though I think it's interesting to have a snapshot of what was done
over that short period. Memory control and leak avoidance were a high priority.

# AI use
- explore and discuss topics
- forward to material and documentation
- shell's pipeline structure and guidelines
- code review on code written by us and potential issues detection

## (AI use-disclaimer):
- DOs: it was used to argue over topics, dive deep in topics, extensive
  conversations over why something works the way it does, and reinforce the understanding of certain parts of bash behavior (along with documentation
  forwarding and reading).

- DONTs: It was never used to let it write code for me, rather, it provided fix-
  suggestions or some naming advice here and there.

# Resources:

## chdir()
- https://man7.org/linux/man-pages/man2/chdir.2.html
## getcwd()
- https://man7.org/linux/man-pages/man3/getcwd.3.html
## getenv()
- https://man7.org/linux/man-pages/man3/getenv.3.html
## open()
- http://man7.org/linux/man-pages/man2/open.2.html
- https://pubs.opengroup.org/onlinepubs/7908799/xsh/open.html