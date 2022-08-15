import java.io.*;
import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Scanner;

public class Main {
    public static String decimalToBinary(int num,int digit)
    {
        char[] binary = new char[digit];
        for(int i=0;i<digit;i++){
            binary[i]='0';
        }
        int id = digit-1;
        while (num > 0) {
            binary[id--] = (char) ('0'+(num % 2));
            num = num / 2;
        }
        return String.valueOf(binary);

    }
    public static String getHexString(String binaryString){
        String hex="";
        for(int i=0;i<=12;i+=4){
            String str=binaryString.substring(i,i+4);
            int mul=1;
            int bin=0;
            for(int j=3;j>=0;j--){
                if(str.charAt(j)=='1'){
                    bin+=mul;
                }
                mul*=2;
            }
            hex+=Integer.toHexString(bin);
        }
        return hex;
    }
    public static void main(String[] args) throws IOException {
        Scanner scanner=new Scanner(new FileInputStream("input.txt"));
        FileWriter fileWriter=new FileWriter("output.txt");
        FileWriter fileWriter2=new FileWriter("output2.txt");
        fileWriter.write( "v2.0 raw\n" );
        HashMap<String,String[]> opCodeHashMap=OpCodeConverter.getHashMapForOpcode();
        HashMap<String,String> registerHashMap=OpCodeConverter.getHashMapForRegister();
        HashMap<String,Integer> labelHashMap=OpCodeConverter.getHashMapForLabel();
        int address=0;
        while (scanner.hasNextLine()){
            String string=scanner.nextLine();
            String[] ara1=string.split(" ");
            if(ara1.length==1){
                continue;
            }
            String[] ara2=ara1[1].split(",");
            String[] opCodeHashValue=opCodeHashMap.get(ara1[0]);
            String machineCode=opCodeHashValue[1];
            if(opCodeHashValue[0].equals("R")){
                machineCode+=registerHashMap.get(ara2[1]);
                machineCode+=registerHashMap.get(ara2[2]);
                machineCode+=registerHashMap.get(ara2[0]);
            }
            if(opCodeHashValue[0].equals("S")){
                machineCode+=registerHashMap.get(ara2[1]);
                machineCode+=registerHashMap.get(ara2[0]);
                int shiftAmount=Integer.parseInt(ara2[2]);
                machineCode+=decimalToBinary(shiftAmount,4);
            }
            if(opCodeHashValue[0].equals("I")){
                if(ara1[0].equals("beq")||ara1[0].equals("bneq")){
                    machineCode+=registerHashMap.get(ara2[0]);
                    machineCode+=registerHashMap.get(ara2[1]);
                    int labelAddress=labelHashMap.get(ara2[2]);
                    int offset=labelAddress-address-1;
                    if(offset>=0){
                        machineCode+=decimalToBinary(offset,4);
                    }
                    else{
                        String str=Integer.toBinaryString(offset);
                        String str2=str.substring(str.length()-4);
                        machineCode+=str2;
                    }
                }
                else if(ara1[0].equals("lw")||ara1[0].equals("sw")){
                    int index=ara2[1].indexOf('(');
                    machineCode+=registerHashMap.get(ara2[1].substring(index+1,ara2[1].length()-1));
                    machineCode+=registerHashMap.get(ara2[0]);
                    int value=Integer.parseInt(ara2[1].substring(0,index));
                    machineCode+=decimalToBinary(value,4);
                }
                else{
                    machineCode+=registerHashMap.get(ara2[1]);
                    machineCode+=registerHashMap.get(ara2[0]);
                    int immediate=Integer.parseInt(ara2[2]);
                    if(immediate>=0){
                        machineCode+=decimalToBinary(immediate,4);
                    }
                    else{
                        String str=Integer.toBinaryString(immediate);
                        String str2=str.substring(str.length()-4);
                        machineCode+=str2;
                    }
                }
            }
            if(opCodeHashValue[0].equals("J")){
                int labelAddress=labelHashMap.get(ara2[0]);
                machineCode+=decimalToBinary(labelAddress,8);
                machineCode+="0000";
            }
            String hex=getHexString(machineCode);
            machineCode+="\n";
            hex+="\n";
            fileWriter.write(hex);
            fileWriter2.write(machineCode);

            address++;
        }
        fileWriter.close();
        fileWriter2.close();
    }
}
