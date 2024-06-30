/*
 * Simple.java
 *
 * Created on February 6, 2004, 4:16 PM
 */

package simple.java;

import java.net.ServerSocket;
import java.net.Socket;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.IOException;
import java.io.Serializable;

/**
 *
 * @author  nvojinov
 */
public class Simple implements Serializable
{
    Simple  mInstance = null;
    int     mNo = 0;
    
    static int indent = 0;
    
    private static final long serialVersionUID = 0;

    public Simple(int number)
    {
        number--;
        mNo = number;
        if(number > 0)
            mInstance = new Simple(number);
    }
    
    /** Creates a new instance of Simple */
    public Simple() 
    {
    }
    
    public String toString()
    {
        indent++;
        String aString = new String();
        for(int i = 0; i < indent; i++)
            aString += "\t";
        aString += " = [" + super.toString() + "]{\n";
        for(int i = 0; i < indent; i++)
            aString += "\t";
        aString += "mNo = " + mNo + "\n";

        for(int i = 0; i < indent; i++)
            aString += "\t";
        if(mInstance != null)
            aString += "mInstance" + mInstance + "\n";
        else
            aString += "mInstance = [" + mInstance + "]\n";
        
        for(int i = 0; i < indent; i++)
            aString += "\t";
        aString += "}";
        
        indent--;
        return(aString);
    }
    
    private static void writeBytes(ObjectOutputStream output) throws IOException
    {
        byte[] byteBuf = { 97, 98, 99 };
        output.write(byteBuf);
        output.write(byteBuf, 1, 2);
        output.write(3);
        output.writeBytes("Hellow from Java!");
        output.writeChars("Next message from Java.");
    }
    
    private static void writeBuiltinTypes(ObjectOutputStream output) throws IOException
    {
        output.writeBoolean(true);
        output.writeByte(102);
        output.writeChar('a');
        output.writeDouble(1234567890.0987654321);
        output.writeFloat((float)1234.56789);
        output.writeInt(0x10000000);
        output.writeLong(0x1000000000000000L);
        output.writeShort(0x1000);
    }
    
    private static void writeBuiltinArrays(ObjectOutputStream output) throws IOException
    {
        boolean[] bools = {false, true};
        output.writeObject(bools);
        byte[] bytes = {(byte)0xff};
        output.writeObject(bytes);
        char[] chars = {'@', '\123'};
        output.writeObject(chars);
        double[] doubles = {};
        output.writeObject(doubles);
        float[] floats = {(float)-3214.54321, (float)21, (float)0, (float)0.0002};
        output.writeObject(floats);
        int[] ints = {0, 22, 43, -11, 1, 33};
        output.writeObject(ints);
        long[] longs = {-1L, 0L};
        output.writeObject(longs);
        short[] shorts = {(short)0xffff, (short)0x7fff, (short)0};
        output.writeObject(shorts);
    }
    
    private static void writeObjects(ObjectOutputStream output) throws IOException
    {
        output.writeObject(new Boolean(false));
        output.writeObject(new Byte((byte)110));
        output.writeObject(new Character('x'));
        output.writeObject(new Double(987654321.123456789));
        output.writeObject(new Float(9876.54321));
        output.writeObject(new Integer(-333));
        output.writeObject(new Long(-1));
        output.writeObject(new Short((short)31));
        output.writeObject("Java String Object");
    }
    
    private static void writeObjectArrays(ObjectOutputStream output) throws IOException
    {
        Boolean[] bools = {new Boolean(true), new Boolean(false), new Boolean(false), new Boolean(true)};
        output.writeObject(bools);
        Byte[] bytes = {new Byte((byte)-1), new Byte((byte)1)};
        output.writeObject(bytes);
        Character[] chars = {new Character('a'), new Character('c')};
        output.writeObject(chars);
        Double[] doubles = {new Double(987654321.0123456789), new Double(-1), new Double(1.1), new Double(1.112), new Double(1.11111)};
        output.writeObject(doubles);
        Float[] floats = {new Float((float)-3214.54321)};
        output.writeObject(floats);
        Integer[] ints = {new Integer(0), new Integer(-22), new Integer(43), new Integer(-11), new Integer(1), new Integer(33)};
        output.writeObject(ints);
        Long[] longs = {new Long(0x0100000000000000L), new Long(-2L), new Long(5L), new Long(0L)};
        output.writeObject(longs);
        Short[] shorts = {new Short((short)1), new Short((short)2), new Short((short)3)};
        output.writeObject(shorts);
        String[] strings = {"Java Base", "Java 2"};
        output.writeObject(strings);
    }

    public static Thread doServer()
    {
        return new Thread()
        { 
            public void run() 
            {
                try
                {
                    ServerSocket serverSocket = new ServerSocket(21211);
                    Socket socket = serverSocket.accept();
                    ObjectOutputStream output = 
                                new ObjectOutputStream(socket.getOutputStream()); 

                    Simple.writeBytes(output);
                    Simple.writeBuiltinTypes(output);
                    Simple.writeBuiltinArrays(output);
                    Simple.writeObjects(output);
                    Simple.writeObjectArrays(output);

                    Object[] objectArray = {    new Boolean(true) ,
                                                new Byte((byte)1),
                                                new Character('1'),
                                                new Double(1),
                                                new Integer(1) };
                    output.writeObject(objectArray);
                   
                    Simple aSimple = new Simple(5);
                    output.writeObject(aSimple);
                    output.close();
                }
                catch(Exception e)
                {
                    e.printStackTrace();
                }
            } 
        };
    }
    

    private static void readBytes(ObjectInputStream input) throws IOException
    {
        System.out.println("\n readBytes");
        byte message[] = new byte[11];
        input.read(message, 0, 11);
        int aInt = input.read();
        byte message2[] = new byte[51];
        input.read(message2);
        
        System.out.println(new String(message, 0, 11));
        System.out.println(new String(message2, 0, 11));
        System.out.println(new String(message2, 11, 40, "UTF-16BE"));
    }

    private static void readBuiltinTypes(ObjectInputStream input) throws IOException
    {
        System.out.println("\n readBuiltinTypes");
        boolean aBoolean = input.readBoolean();
        byte aByte = input.readByte();
        char aChar = input.readChar();
        double aDouble = input.readDouble();
        float aFloat = input.readFloat();
        int aInt = input.readInt();
        long aLong = input.readLong();
        short aShort = input.readShort();
        
        System.out.println( "" + aBoolean + ", " + aByte + ", " + aChar);
        System.out.println( "" + aDouble + ", " + aFloat + ", " + aInt);
        System.out.println( "" + aLong + ", " + aShort);
    }

    private static void readBuiltinArrays(ObjectInputStream input) throws IOException, ClassNotFoundException
    {
        System.out.println("\n readBuiltinArrays");
        boolean bools[] = (boolean[])input.readObject();
        byte bytes[] = (byte[])input.readObject();
        char chars[] = (char[])input.readObject();
        double doubles[] = (double[])input.readObject();
        float floats[] = (float[])input.readObject();
        int ints[] = (int[])input.readObject();
        long longs[] = (long[])input.readObject();
        short shorts[] = (short[])input.readObject();
        
        System.out.print( "bools = {" );
        for(int i = 0; i < bools.length; i++)
        {
            System.out.print(bools[i]);
            System.out.print(", ");
        }
        System.out.println("}");
        
        System.out.print( "bytes = {" );
        for(int i = 0; i < bytes.length; i++)
        {
            System.out.print(bytes[i]);
            System.out.print(", ");
        }
        System.out.println("}");
        
        System.out.print( "chars = {" );
        for(int i = 0; i < chars.length; i++)
        {
            System.out.print(chars[i]);
            System.out.print(", ");
        }
        System.out.println("}");
        
        System.out.print( "doubles = {" );
        for(int i = 0; i < doubles.length; i++)
        {
            System.out.print(doubles[i]);
            System.out.print(", ");
        }
        System.out.println("}");
        
        System.out.print( "floats = {" );
        for(int i = 0; i < floats.length; i++)
        {
            System.out.print(floats[i]);
            System.out.print(", ");
        }
        System.out.println("}");
        
        System.out.print( "ints = {" );
        for(int i = 0; i < ints.length; i++)
        {
            System.out.print(ints[i]);
            System.out.print(", ");
        }
        System.out.println("}");
        
        System.out.print( "longs = {" );
        for(int i = 0; i < longs.length; i++)
        {
            System.out.print(longs[i]);
            System.out.print(", ");
        }
        System.out.println("}");
        
        System.out.print( "shorts = {" );
        for(int i = 0; i < shorts.length; i++)
        {
            System.out.print(shorts[i]);
            System.out.print(", ");
        }
        System.out.println("}");
     }

    private static void readObjects(ObjectInputStream input) throws IOException, ClassNotFoundException
    {
        System.out.println("\n readObjects");
        Boolean boolObj = (Boolean)input.readObject();
        Byte byteObj = (Byte)input.readObject(); 
        Character charObj = (Character)input.readObject();
        Double doubleObj = (Double)input.readObject();
        Float floatObj = (Float)input.readObject();
        Integer intObj = (Integer)input.readObject();
        Long longObj = (Long)input.readObject();
        Short shortObj = (Short)input.readObject();
        String aString = (String)input.readObject();

        System.out.println( "" + boolObj + ", " + byteObj + ", " + charObj);
        System.out.println( "" + doubleObj + ", " + floatObj + ", " + intObj);
        System.out.println( "" + longObj + ", " + shortObj + ", " + aString + "'");
}

    private static void readObjectArrays(ObjectInputStream input) throws IOException, ClassNotFoundException
    {
        System.out.println("\n readObjectArrays");
        Boolean bools[] = (Boolean[])input.readObject();
        Byte bytes[] = (Byte[])input.readObject();
        Character chars[] = (Character[])input.readObject();
        Double doubles[] = (Double[])input.readObject();
        Float floats[] = (Float[])input.readObject();
        Integer ints[] = (Integer[])input.readObject();
        Long longs[] = (Long[])input.readObject();
        Short shorts[] = (Short[])input.readObject();
        String strings[] = (String[])input.readObject();
        
        System.out.print( "bools = {" );
        for(int i = 0; i < bools.length; i++)
        {
            System.out.print(bools[i]);
            System.out.print(", ");
        }
        System.out.println("}");
        
        System.out.print( "bytes = {" );
        for(int i = 0; i < bytes.length; i++)
        {
            System.out.print(bytes[i]);
            System.out.print(", ");
        }
        System.out.println("}");
        
        System.out.print( "chars = {" );
        for(int i = 0; i < chars.length; i++)
        {
            System.out.print(chars[i]);
            System.out.print(", ");
        }
        System.out.println("}");
        
        System.out.print( "doubles = {" );
        for(int i = 0; i < doubles.length; i++)
        {
            System.out.print(doubles[i]);
            System.out.print(", ");
        }
        System.out.println("}");
        
        System.out.print( "floats = {" );
        for(int i = 0; i < floats.length; i++)
        {
            System.out.print(floats[i]);
            System.out.print(", ");
        }
        System.out.println("}");
        
        System.out.print( "ints = {" );
        for(int i = 0; i < ints.length; i++)
        {
            System.out.print(ints[i]);
            System.out.print(", ");
        }
        System.out.println("}");
        
        System.out.print( "longs = {" );
        for(int i = 0; i < longs.length; i++)
        {
            System.out.print(longs[i]);
            System.out.print(", ");
        }
        System.out.println("}");
        
        System.out.print( "shorts = {" );
        for(int i = 0; i < shorts.length; i++)
        {
            System.out.print(shorts[i]);
            System.out.print(", ");
        }
        System.out.println("}");
    }

    public static Thread doClient()
    {
        return new Thread()
        { 
            public void run() 
            {
                try
                {
                    Socket socket = new Socket("localhost", 21212);
                    ObjectInputStream input = 
                                new ObjectInputStream(socket.getInputStream()); 
                    
                    Simple.readBytes(input);
                    Simple.readBuiltinTypes(input);
                    Simple.readBuiltinArrays(input);
                    Simple.readObjects(input);
                    Simple.readObjectArrays(input);

                    Object objectArray[] = (Object[])input.readObject();
               
                    Simple aSimple = (Simple)input.readObject();

                     System.out.println("\n doClient");
                    System.out.print("objectArray = {");
                    for(int i = 0; i < objectArray.length; i++)
                        System.out.print(objectArray[i] + ", ");
                    System.out.println("}");
                   
                    System.out.println("simple" + aSimple);
                    socket.close();
                }
                catch(Exception e)
                {
                    e.printStackTrace();
                }
            } 
        };
    }
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) 
    {
        Thread server = Simple.doServer();
        Thread client = Simple.doClient();
        server.start();
        client.start();
    }
}
