<h1 align="center">📊 CDataframe</h1>
<p align="center"><i>A mini DataFrame system in pure C — low-level performance meets data science</i></p>

<p align="center">
  <img src="https://img.shields.io/badge/Language:-C-00599C?style=flat-square&logo=c&logoColor=white" />
  <img src="https://img.shields.io/badge/Platform:-Windows-0078D6?style=flat-square&logo=windows&logoColor=white" />
  <img src="https://img.shields.io/badge/Research-Driven-8E2DE2?style=flat-square&logo=googlescholar&logoColor=white" />
  <img src="https://img.shields.io/badge/Version-1.0.1-27AE60?style=flat-square&logo=semantic-release&logoColor=white" />
</p>


---

## 👥 Project Team

- 👤 **Eden Elfassy**  
- 👤 **Bryan Tewouda**  
- 👤 **Adam Assayag**

---

## 🔗 Repository

📎 [👉 Access the GitHub Repository](https://github.com/GingaShift/CDataframe-Eden-Adam-Bryan-PP)  

📂 **Windows executable available at**:  
`/x64/Release/CDataframe.exe`

---

## 🚀 Key Features

> ⚙️ Manipulate structured data like a Python DataFrame… but in pure C!

✅ Create a CDataframe  
✅ Add/remove columns  
✅ Insert values into cells  
✅ Display partial or complete tables  
✅ Search values, rename columns, sort by column  
✅ Generate statistics on values (occurrences, frequency, etc.)  
✅ Save results as `.csv`  

🆕 **Version 2.0 (in progress)** with:  
- Functions fully written in English  
- Modular structuring with `#pragma region`  

---

## 🛠️ Installation (Windows + Visual Studio 2022)

1. 📥 Install [Visual Studio 2022 Community](https://visualstudio.microsoft.com/vs/community/)  
   ➕ Include the **C++ workload**

2. 🧲 Clone the repository:  
   `Git > Clone Repository` → paste repo URL  

3. 📁 Select a local folder and **clone**

4. ▶️ Press **F5** to run the project  

5. 📂 To reopen the project: double-click `CDataframe.sln`

---

## ⚙️ Important Visual Studio Settings

### ✅ Fixing `scanf_s`:
1. Right-click project → **Properties**  
2. Navigate: `C/C++ > General > SDL checks` → **No (/GS-)**

### ✅ Fixing `E1072` error:
1. Navigate: `C/C++ > Language > C Language Standard`  
2. Choose: `ISO C17 (/std:c17)` ✅  
_(C11 is also compatible)_

---

## 🧪 Quick Demo

🎬 **3-step test run**:  
1. Launch program → Home menu  
2. Type `11` → Create an empty CDataframe (name it)  
3. Type `15` → Auto-fill with columns & sample data  

🎯 Examples:  
- `21` → Show entire Dataframe  
- `22` → Show first 10 rows (`-1` columns, `10` rows)  
- 🔍 Try options: sort, search, add column, rename, save  

⚠️ **Do not run command `38`...**  
You’ve been warned 😈  

---

## 🖼️ Screenshots

<p align="center">
  <!-- Screenshot 1 -->
 <img width="800" height="656" alt="image" src="https://github.com/user-attachments/assets/c5989685-32dd-4201-9412-b76235bf39a8" />
  <br><em>🔹 Main program interface</em>
</p>

<p align="center">
  <!-- Screenshot 2 -->

  <img width="684" height="272" alt="image" src="https://github.com/user-attachments/assets/55e07e5f-e607-4172-a3ee-c32f2065b74a" />
  <br><em>🔹 Example: inserting and displaying tabular data</em>
</p>



---

## 💡 About the Code

The project is modularized in versions:  

```c
#pragma region CDataframe 1
// Functions v1 (French)
#pragma endregion

#pragma region CDataframe 2
// Functions v2+ (English + modular)
#pragma endregion
