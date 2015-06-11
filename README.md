# RawrOS

#### What?  An operating system?  Why?
There's not really a good answer for that.  It seemed like a good idea at the
time.

#### Ok... Why "Rawr"?
It's scary.  Scary like tiger.  Although it's barely a tiger cub at the moment.
  Right now it's more "scary" how little functionality there is.  I don't know,
 really, that's what I came up with.  Is it more strange than "ubuntu"?

#### Alright, alright, so what can it do?
More like what doesn't it do?  I mean it boots up and spits some text out into
the VGA buffer and everything.  What more do you really want from a machine
than to just turn it on and have it say, "Hello sir!"  I mean it really has it 
all.  Sick of dealing with printer drivers?  Worry no more because this has 
no printer drivers.  Whatsoever.  It also doesn't support any kind of printing.
  It's not perfect.

#### Wait, so it only boots up and says hello?
Well, I mean when you put it like that...

### Alright, so suppose I want to compile this for some reason...
So I've only successfully built this on a Linux host and have only tested it 
in an emulator.  That being said, the Makefile should do just fine.  You'll 
need gcc, ld, nasm, bochs, and make.  Supposing those are in order, if you do:
```
make
make run
```
You should then be looking at an emulator screen loaded up with the OS image.

#### License?
I have chosen the MIT license, because why not?  If someone wants to use
some of this, go for it.

#### Neat!
I thought so too.
