import os,time
#def createKB():
def createB(dirname,filesize):
    filename= os.path.join(dirname,'Test80MB.txt')
    no_of_bytes =10000000 #jus change this value to generate the file sizes.
    compute(filename,filesize,no_of_bytes)



def compute(filename,filesize,noB):
    count =0
    time_towrite =0.5
    start= time.time()
    while True:
        try:
            data ="This is Tanveer Anand's PA1 submission."
            
            counter = int(8*noB*filesize/len(data))
            try:
                f = open(filename,"w")
            except:
                raise
            for i in range(0,counter):
                f.write(str(data))
            f.close()
            
        except:
            raise
        count+=1
        difference = time.time()-start
        if difference > time_towrite:
            break
    return ((count*filesize)/difference) 
    
#def CreateLargeB(filename,filesize):
    

def getfileName(dirname):
    filesize = 1
    createB(dirname,filesize)
    #createKB(dirname.filesize)

                   

    

if __name__ =="__main__":
    dirname = os.getcwd()
    val=getfileName(dirname)
