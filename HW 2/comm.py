import random, sys
from optparse import OptionParser


def main():
    masgVerson = "%prog 2.0"                                                                                                                                                      
    masgUsage = "%prog [-123u] FILE1 FILE2"                                                                                                                                       
    parser = OptionParser(version=masgVerson, usage=masgUsage)  
    parser.add_option("-u", action="store_true", dest="un", default=0)
    parser.add_option("-1", action="store_true", dest="one", default=0)
    parser.add_option("-2", action="store_true", dest="two", default=0)
    parser.add_option("-3", action="store_true", dest="three", default=0)
    options, argument = parser.parse_args(sys.argv[1:])

    un=options.un
    one=options.one
    two=options.two
    three=options.three
    
    if len(argument)!=2:
        parser.error("Wrong operand number")
    
    
    fileOne=argument[0]
    fileTwo=argument[1]
    lineOne = []
    lineTwo =[]

    if fileTwo=="-":
        lineOne=sys.stdin.readlines()

        try:
            f2 = open (fileOne, 'r')
            lineTwo = f2.readlines()
            f2.close()
        except:
            parser.error("Invalid file type")

    else:
        try:
            f1 = open (fileOne, 'r')
            f2 = open (fileTwo, 'r')
            lineOne = f1.readlines()
            lineTwo = f2.readlines()
            f1.close()
            f2.close()
        except:
            parser.error("Invalid file")
        
        
    sp="        "
 
    n1 = len(lineOne)
    n2 = len(lineTwo)
    column1 = []
    column2 = []
    column3 = []
    n=0
    if un==0:
        column3=[i for i in lineOne if i in lineTwo]
        for i in column3:
            if i in lineTwo:
                lineTwo.remove(i)
        for i in column3:
            if i in lineOne:
                lineOne.remove(i)
        t=sorted(lineOne+column3+lineTwo)

        column1=lineOne
        column2=lineTwo
        for i in t:
            if i in column1 and one!=1:
                sys.stdout.write(i)
            
            if i in column2 and one!=1 and two!=1:
                sys.stdout.write(sp+i)
            elif i in column2 and one==1 and two!=1:
                sys.stdout.write(i)

            if i in column3 and one!=1 and two!=1 and three!=1:
                sys.stdout.write(sp+sp+i)
            elif i in column3 and one==1 and two!=1 and three!=1:
                sys.stdout.write(sp+i)
            elif i in column3 and one!=1 and two==1 and three!=1:
                sys.stdout.write(sp+i)
            elif i in column3 and one==1 and two==1 and three!=1:
                sys.stdout.write(i)

    if un==1:
        column3=[i for i in lineOne if i in lineTwo]
        for i in column3:
            if i in lineTwo:
                lineTwo.remove(i)
        for i in lineOne:
            if i in column3 and one!=1 and two!=1 and three!=1:
                sys.stdout.write(sp+sp+i)
            elif i in column3 and one==1 and two!=1 and three!=1:
                sys.stdout.write(sp+i)
            elif i in column3 and one!=1 and two==1 and three!=1:
                sys.stdout.write(sp+i)
            elif i in column3 and one==1 and two==1 and three!=1:
                sys.stdout.write(i)
            elif i not in column3 and one!=1:
                sys.stdout.write(i)
        for i in lineTwo:
            if one!=1 and two!=1:
                sys.stdout.write(sp+i)
            elif one==1 and two!=1:
                sys.stdout.write(i)
                                                                                                                                                                                                                                                                                                                    
if __name__ == "__main__":
    main()

