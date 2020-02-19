package edu.sdsu.cs;
//package token2;

//Program 1, Files and Lists, by Chris McDaniel (cssc0724) and Kosuke Takahashi (cssc0758)

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class App {

    public static void main(String[] args) throws IOException {


        String runTimeArg = args[0];

        String currentFileLoc = new java.io.File( "." ).getCanonicalPath();

        if (runTimeArg.length() > 0) {
            currentFileLoc = runTimeArg;
        }

        ArrayList<String> fileMainList = new ArrayList<String>();
        File currentDir = new File(currentFileLoc);
        fileMainList = obtainFileList(currentDir, fileMainList);
        Integer fListEnd = fileMainList.size()-1;
        Integer fListStart = 0;

        while (fListEnd >= 0) {
            String fileRun = fileMainList.get(fListStart);
            String longestLineLength = "a";
            File file = new File(fileRun);

            ArrayList<String> eachSeparateLine = new ArrayList<>();
            ArrayList<String> eachIndividualToken = new ArrayList<>();
            ArrayList<String> caseInsensitiveIndividualToken = new ArrayList<>();
            ArrayList<Integer> caseSensitiveTokenCount = new ArrayList<>();

            readFileCmd(eachSeparateLine, eachIndividualToken, file);

            //longestLineLength produces "Length of Longest
            //Line in File" and "Average Line Length"
            longestLineLength = lngstLine(eachSeparateLine, longestLineLength);

            //Number of all space-delineated tokens in file
            int allTokensInFile = eachIndividualToken.size();
            String totalTokens = ("Number of all space-delineated "
                    + "tokens in file: \n" + allTokensInFile);
            String mostFreqTokenFinal = "a";
            String caseSensitiveTokensFinal = "a";

            String[] mostFreqTokenFinal1 = caseSenseTokens
                    (eachIndividualToken, caseSensitiveTokenCount,
                            mostFreqTokenFinal, caseSensitiveTokensFinal);

            //Obtain all Case-Insensitive tokens
            insensitiveTokensSave
                    (eachIndividualToken,caseInsensitiveIndividualToken);

            //Obtain number of unique space-delineated tokens (case sensitive)
            String caseInsensitiveTokens = caseInsenseTokens
                    (caseInsensitiveIndividualToken);

            //Obtain most frequently occurring token,
            //10 most and 10 least occurring tokens
            //case insensitive
            String insensitiveTokenTotal[] = insensitiveTokensData
                    (eachIndividualToken, caseInsensitiveIndividualToken);

            ArrayList<String> fileWrite = new ArrayList<>();
            fileWrite.add(longestLineLength);
            fileWrite.add("\n\n");
            fileWrite.add(mostFreqTokenFinal1[0]);
            fileWrite.add("\n\n");
            fileWrite.add(caseInsensitiveTokens);
            fileWrite.add("\n\n");
            fileWrite.add(totalTokens);
            fileWrite.add("\n\n");
            fileWrite.add(mostFreqTokenFinal1[1]);
            fileWrite.add("\n\n");
            fileWrite.add(insensitiveTokenTotal[0]);
            fileWrite.add("\n\n");
            fileWrite.add(insensitiveTokenTotal[1]);
            fileWrite.add("\n\n");
            fileWrite.add(insensitiveTokenTotal[2]);
            fileWrite.add("\n\n");

            writeToFiles(fileWrite, fileMainList.get(fListStart));
            fListEnd--;
            fListStart++;
        }

    }


    private static void readFileCmd(ArrayList<String> lines1by1,
                                    ArrayList<String> indivTokens, File file1){

        try {
            FileReader reader = new FileReader(file1);
            BufferedReader buffReader = new BufferedReader(reader);
            String rdLine;

            while((rdLine = buffReader.readLine()) != null) {

                if (!rdLine.isEmpty()) {
                    List<String> splitStr = Arrays.asList
                            (rdLine.split("\\t|\\s+|\\r|\\n"));
                    ArrayList<String> aListTokens = new ArrayList<>(splitStr);

                    for (int gg = 0; gg < aListTokens.size(); gg++) {

                        if (aListTokens.get(gg).isEmpty()) {
                            aListTokens.remove(gg);
                            gg--;
                            continue;
                        }
                        int charChk = aListTokens.get(gg).charAt(0);

                        if (charChk > 128 || charChk < 0 ||
                                aListTokens.get(gg).isEmpty()) {
                            aListTokens.remove(gg);
                            gg--;
                        }
                    }

                    String lines1by2 = rdLine.replaceAll("\\t", "");
                    lines1by1.add(lines1by2);
                    indivTokens.addAll(aListTokens);
                }
            }
            buffReader.close();

        }
        catch(IOException e){
        }
    }//readFileCmd Method End


    //Length of longest line in file
    private static String lngstLine(ArrayList<String>
                                            eachLine, String longLine) {

        int newCount = 0;
        int length = 0;
        int lineLengthCheck = 0;
        int lineLengthCheckFin = 0;
        String bestLine = "a";
        String bestLineTotal = "a";

        for (int i = 0; i < eachLine.size(); i++) {

            String lineCheck =  eachLine.get(i);
            length = lineCheck.length();
            lineLengthCheck += length;

            if (length > newCount) {
                newCount = length;
                bestLine = lineCheck;
            }
        }

        lineLengthCheckFin = (lineLengthCheck / eachLine.size());
        bestLineTotal = "Longest Line in File: \n" + newCount +
                " characters: \n\"" + bestLine+ "\"\n\n" +
                "\nAverage Line Length: \n" + lineLengthCheckFin + " Characters";
        return bestLineTotal;

    }//End lngstLine Method


    private static String[] caseSenseTokens(ArrayList<String> token4,
                                            ArrayList<Integer> tokenCountSens, String mostFreqTokenPass,
                                            String caseSenseTokensFinal) {

        ArrayList<String> caseSenseTest = new ArrayList<>(token4);
        ArrayList<String> caseSense = new ArrayList<>();

        outerloop:
        for (int i = 0;  i == caseSense.size(); i++) {
            if (!caseSenseTest.isEmpty()) {
                caseSense.add(caseSenseTest.get(0));
                tokenCountSens.add(i, 0);
            }

            for (int k = 0; k != caseSenseTest.size() + 1; k++) {
                while (caseSenseTest.contains(caseSense.get(i))) {

                    caseSenseTest.remove(caseSense.get(i));
                    tokenCountSens.set(i, tokenCountSens.get(i) + 1);
                }
                if (caseSenseTest.size() == 0) {
                    break outerloop;
                }
            }
        }

        int mostFreqT = tokenCountSens.get(0);
        int indexOfFreqT = 0;

        for (int inc = 1; inc < tokenCountSens.size(); inc++) {
            if (tokenCountSens.get(inc) > mostFreqT) {
                mostFreqT = tokenCountSens.get(inc);
                indexOfFreqT = inc;
            }
        }

        String aa = caseSense.get(indexOfFreqT);
        mostFreqTokenPass = "Most frequently occurring token(s): \n" + aa;
        int caseSenseTokensFin = caseSense.size();
        caseSenseTokensFinal = "Number of unique space-delineated tokens"
                + " (case-sensitive): \n" + caseSenseTokensFin + " tokens";

        return new String[] {caseSenseTokensFinal, mostFreqTokenPass};
    }//End



    private static String caseInsenseTokens(ArrayList<String> token4) {

        ArrayList<String> caseSenseTest = new ArrayList<>(token4);
        ArrayList<String> caseSense = new ArrayList<>();

        outerloop:
        for (int i = 0;  i == caseSense.size(); i++) {
            if (!caseSenseTest.isEmpty()) {
                caseSense.add(caseSenseTest.get(0));

            }
            for (int k = 0; k != caseSenseTest.size() + 1; k++) {

                while (caseSenseTest.contains(caseSense.get(i))){
                    caseSenseTest.remove(caseSense.get(i));
                }
                if (caseSenseTest.size() == 0) {
                    break outerloop;
                }

            }

        }

        int caseSenseTokensFin = caseSense.size();
        String caseSenseTokensFinal = "Number of unique "
                + "space-delineated tokens (case-insensitive): \n" +
                caseSenseTokensFin + " tokens";
        return caseSenseTokensFinal;
    }


    private static void insensitiveTokensSave
            (ArrayList<String> token5, ArrayList<String> insensT) {

        insensT.addAll(token5);
        String toChange = "a";

        for (int tokIdx = 0; tokIdx < insensT.size(); tokIdx++) {
            toChange = insensT.get(tokIdx);
            toChange = toChange.toLowerCase();
            insensT.set(tokIdx, toChange);
        }
    }//End insensitiveTokenSave Method


    private static String[] insensitiveTokensData (ArrayList<String>
                                                           token6, ArrayList<String> insensitiveTokens) {

        ArrayList<String> insensitiveTokenForUse = new ArrayList<>();
        ArrayList<String> finalTokenForUse = new ArrayList<>();
        ArrayList<Integer> insensitiveTokenCount = new ArrayList<>();
        insensitiveTokenForUse.addAll(insensitiveTokens);

        for (int zz = 0; !insensitiveTokenForUse.isEmpty(); zz++) {

            finalTokenForUse.add(insensitiveTokenForUse.get(0));
            insensitiveTokenCount.add(zz, 0);

            while (insensitiveTokenForUse.contains(finalTokenForUse.get(zz))) {

                insensitiveTokenForUse.remove(finalTokenForUse.get(zz));
                insensitiveTokenCount.set(zz, insensitiveTokenCount.get(zz) + 1);

            }
        }

        int tVal1;
        String tVal2;
        boolean sortBool = true;
        ArrayList<Integer> most = new ArrayList<>(insensitiveTokenCount);
        ArrayList<String> mostStr = new ArrayList<>(finalTokenForUse);

        while (sortBool == true) {
            sortBool = false;
            for(int getV = 0;  getV < most.size() - 1; getV++) {
                if (most.get(getV) > most.get(getV+1)) {

                    tVal1 = most.get(getV);
                    tVal2 = mostStr.get(getV);
                    most.set(getV, most.get(getV+1));
                    most.set(getV + 1, tVal1);
                    mostStr.set(getV,  mostStr.get(getV+1));
                    mostStr.set(getV + 1, tVal2);
                    sortBool = true;

                }
            }
        }

        String mostFrequentOccurringToken = "Count of most Frequently "
                + "Occurring token (case-insensitive): \n" + most.get(mostStr.size()-1);

        String mostFrequentCountTurnIn = "10 most frequent tokens with "
                + "their counts (case-insensitive): \n" + mostStr.get(mostStr.size()-1)
                + " " + most.get(most.size()-1) + "\n" + mostStr.get(mostStr.size()-2)
                + " " + most.get(most.size()-2) + "\n"+ mostStr.get(mostStr.size()-3)
                + " " + most.get(most.size()-3) + "\n" + mostStr.get(mostStr.size()-4)
                + " " + most.get(most.size()-4) + "\n"+ mostStr.get(mostStr.size()-5)
                + " " + most.get(most.size()-5) + "\n" + mostStr.get(mostStr.size()-6)
                + " " + most.get(most.size()-6) + "\n"+ mostStr.get(mostStr.size()-7)
                + " " + most.get(most.size()-7) + "\n" + mostStr.get(mostStr.size()-8)
                + " " + most.get(most.size()-8) + "\n"+ mostStr.get(mostStr.size()-9)
                + " " + most.get(most.size()-9) + "\n" + mostStr.get(mostStr.size()-10)
                + " " + most.get(most.size()-10);

        String leastFrequentCountTurnIn = "10 least frequent tokens with "
                + "their counts (case-insensitive): \n" + mostStr.get(0) + " " +
                most.get(0) + "\n" + mostStr.get(1) + " " + most.get(1)
                + "\n"+ mostStr.get(2) + " " + most.get(2) + "\n" +
                mostStr.get(3) + " " + most.get(3) + "\n"+ mostStr.get(4)
                + " " + most.get(4) + "\n" + mostStr.get(5) + " " + most.get(5)
                + "\n"+ mostStr.get(6) + " " + most.get(6) + "\n" +
                mostStr.get(7) + " " + most.get(7) + "\n"+ mostStr.get(8)
                + " " + most.get(8) + "\n" + mostStr.get(9) + " " + most.get(9);


        return new String[] {mostFrequentOccurringToken,
                mostFrequentCountTurnIn, leastFrequentCountTurnIn};
    }


    private static void writeToFiles(ArrayList<String> fileWrite,
                                     String finalWriteF)
            throws IOException {
        String finalWriteFStr = finalWriteF + ".stats";
        BufferedWriter writeToStats = new BufferedWriter
                (new FileWriter(finalWriteFStr));

        for (String str1: fileWrite) {
            writeToStats.write(str1);
        }

        writeToStats.close();
    }//End writeToFiles Method


    private static ArrayList<String> obtainFileList
            (File mainDir, ArrayList<String> fList) {

        try {
            File[] file_Search = mainDir.listFiles();
            for (File fileEx : file_Search) {
                if (fileEx.isDirectory()) {
                    obtainFileList(fileEx, fList);
                }
                else {

                    if (fileEx.getPath().endsWith(".java") ||
                            fileEx.getPath().endsWith(".txt")) {
                        fList.add(fileEx.getCanonicalPath());
                    }
                }
            }
        }
        catch (IOException e) {
            e.printStackTrace();
        }
        return fList;

    }


}//End Class