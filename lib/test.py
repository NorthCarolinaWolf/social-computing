import sys
def main(argv):
    print 'I am python file'+ argv[0]
    
if __name__ == '__main__':     # if the function is the main function ...
    main(sys.argv[1:]) # ...call it

