# Two Hat Security: freelancer contest

Contest entry by Helix [[profile]](https://www.freelancer.com/u/astaroht)

Implementation complete. ~~Saw the contest just a few hours before its ending, still working on a few things.~~ Work remaining only for the concurrent change in the dictionary.
## Performance Report

```bash
siege -c100 --content-type="application/json" '127.0.0.1:5050 POST < ./test/data/testdata.json'
```   


QPS/ Transaction Rate:  ~2500  
Memory usage:           ~1035MB     
     


**For comparison (basic "Hello, world!" server)**  

```bash
siege -c100 '127.0.0.1:5050'
```

QPS/ Transaction Rate:  ~12500  
Memory usage:           ~15MB   

**System Specifications**   

2 cores, 4GB (AWS instances)  


 
## Installation Instructions

Use the package manager [pip](https://pip.pypa.io/en/stable/) to install cffi.

```bash
pip3 install cffi
```  

For MacOs (tested) and Ubuntu (tested) with valid Python3 (with CFFI) & GoLang installations:   

For Windows (untested), alongside valid Python3 & GoLang installations, make sure to use **mingw x86-64** (**not 32 bit** version) with **python pkg-config** setup.   


**To run the server**  

Clone the repo, and in the directory run:

```bash
python3 server.py
```  
Server would start at localhost:5050 [[127.0.0.1:5050]](127.0.0.1:5050)   

**To re-build (hopefully not required for MacOs and Ubuntu)**    

Source files present in **/source** dir. Please use those, delete/replace the boilerplate files in the main dir.  

For shared .so files from .go module  

```bash
go build -buildmode=c-shared -o backend.so
```

For boilerplate code using CFFI to enable python import  

```bash
python3 generateFFI.py. 
```

## How long it took?
**< 1 hour** :  Setup python server (flask) with Go backend (load_json, get_topics, etc.)  
**2 hours**  :    Attempting to get Go FastHttp to talk with Python (i.e. Go calls Python, then Python calls Go), boilerplate communication and runtime clash issue, scrapped.  
**< 1 hour** :  Setup Go net/http server (as in the given [article](https://blog.heroku.com/see_python_see_python_go_go_python_go))  
**< 1 hour** : Switch from net/http backend to fastHttp backend

**Total** : ~ 4 hours  


## Miscellaneous


**~~Currently working~~** on two approaches for Go FastHttp (for contribution):
* ~~One previously scrapped (Go calls Python, then Python calls Go, separate runtimes with boilerplate communication)~~ Scrapped, since not required now.
* ~~Easy one: Python calls Go FastHttp, and also backend, using CFFI (i.e. initiation code is run by python)~~ Completed.

## Scoring checkbox
* Conventional commits ✓
* Single puspose commits ✓
* README.md ✓
* Followed instructions ✓
* QPS position [idk]
* Code smell [please judge]
* Well documented code [please judge]
* Code broken into reasonable peices ✓
* 80% coverage ✓
* 100ms change dictionary ✗ (currenty working)


## Credits

[shazow: gohttplib](https://github.com/shazow/gohttplib) For net/http wrapper from Go