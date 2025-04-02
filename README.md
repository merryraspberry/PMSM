# Field-Oriented Control of a PMSM in PLECS DLL

This repository contains the source code and project files for my Bachelor's thesis titled **"Wybrane aspekty sterowania maszyną synchroniczną z magnesami trwałymi (PMSM)"**, which translates to *Selected Aspects of Control for a Permanent Magnet Synchronous Machine*. The implementation focuses on a DLL-based control module designed for use with the PLECS simulation environment.

##  Project Summary

The aim of this project is to implement Field-Oriented Control (FOC) for a Permanent Magnet Synchronous Machine (PMSM) using:

- Clarke and Park transformations
- PI controllers for speed and current loops
- Delay modeling for control signal simulation
- Reversible dq-ABC transformations

All logic is compiled into a Windows DLL that interfaces with PLECS for simulation.

##  File Structure

| File / Folder      | Description |
|--------------------|-------------|
| `main.c`           | Core logic for control algorithm, invoked by PLECS via DLL interface |
| `PI.c`, `PI.h`     | Proportional-Integral controller with anti-windup logic |
| `transformations.h`| Implements ABC↔dq transformations using Park & Clarke |
| `delay.c`, `delay.h`| Models delay elements for current controllers |
| `DllHeader.h`      | Interface definitions required by PLECS DLL |
| `PMSM1.sln`, `PMSM1.vcxproj` | Visual Studio solution and project files for DLL compilation |

##  Build Instructions

To build the DLL:

1. Open `PMSM1.sln` in **Visual Studio** (2019 or newer).
2. Select your desired build configuration: `Debug` or `Release`.
3. Build the solution to generate `PMSM1.dll`.

##  Inputs

The DLL accepts 7 simulation inputs via the `inputs[]` array:

1. `A`, `B`, `C` – Phase currents
2. `fi` – Electrical angle
3. `w_ref` – Reference angular speed
4. `wm` – Measured speed
5. `id_ref` – Reference d-axis current

##  Outputs

The DLL returns 3 outputs:

- `A_out`, `B_out`, `C_out` – Controlled phase voltages

##  Parameters

The DLL expects the following 10 user parameters in PLECS:

| Index | Parameter |
|-------|-----------|
| 0     | `kp_w` – Speed loop Kp |
| 1     | `ki_w` – Speed loop Ki |
| 2     | `kp_d` – D-axis current loop Kp |
| 3     | `ki_d` – D-axis current loop Ki |
| 4     | `kp_q` – Q-axis current loop Kp |
| 5     | `ki_q` – Q-axis current loop Ki |
| 6     | `Ts` – Sampling time |
| 7     | `sat` – Saturation limit for current controllers |
| 8     | `Imin` – Min PI output |
| 9     | `Imax` – Max PI output |

##  Optional Delay

The controller includes an optional delay (`#define DELAY`) to simulate realistic current control behavior. To enable it, uncomment the `#define DELAY` line in `main.c`.

##  Simulation

Use this DLL with a PLECS model to simulate PMSM control. The model should supply the required inputs and read back the outputs as described.

##  License

This project was created as part of an academic Bachelor's thesis and is intended for educational and research purposes only. © 2025 Michał Makowski

