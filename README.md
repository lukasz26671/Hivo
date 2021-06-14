# Hivo

## What is Hivo?

Hivo is a high-level dynamic, weakly typed programming language.  
Its' JS-Like syntax will make learning a lot easier.  

Main purpose of Hivo is making cross-site requests very simple, with a minimum of effort realistically.  
Underlying level of abstraction provides easy access to OS level functions as well as other language execution.  

## Compatibillity

As of today (14/06/21 or 06/14/21) there's no working Linux and/or Mac OS build.

## Contribution

You are free to contribute to this project. However, you may not use this code or distribute it without any personal agreement.  

#### Run a program

- shell  
```console
foo@bar:~$ Hivo helloworld.hv
```
- Powershell
```powershell
PS C:\users\user> Hivo helloworld.hv 
```
- Cmd
```cmd
C:\users\user Hivo helloworld.hv
```

### Examples


##### Hello World

```javascript
println("Hello, world!");
```

##### Custom function

```javascript
function foo(a)
{
  print(a);
};
```

##### Insertion breakpoints (pause-like)

```javascript

let variable = "John";

pbrkp(); //-> place break point 

//; Press enter/any key to continue...

println(variable); // John
```


