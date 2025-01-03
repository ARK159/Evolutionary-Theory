import matplotlib.pyplot as plt
import numpy as np

timestep=np.arange(24)
N=1200
custlist33 =[]
custlist53 =[]
custlist55 =[]
custlist22 =[]

custlist33.append(N)
custlist53.append(N)
custlist55.append(N)
custlist22.append(N)

valList33 =[]
valList53 =[]
valList55 =[]
valList22 =[]

demand_33=0
demand_53=0
demand_55=0
demand_22=0

for i in timestep:
    demand_33 +=round(int(custlist33[i])*0.02)
    demand_53 +=round(int(custlist33[i])*0.04)
    demand_55 += round(int(custlist55[i]) * 0.07)
    demand_22 += round(int(custlist22[i]) * 0.12)

    next_cust33=round(int(custlist33[i])*0.99)
    next_cust53=round(int(custlist53[i])*0.97)
    next_cust55=round(int(custlist55[i])*0.94)
    next_cust22=round(int(custlist22[i])*0.92)

    sigma_c33 = demand_33/custlist33[i]*np.exp((custlist33[i]-next_cust33)/custlist33[i])
    sigma_c53 = demand_53 / custlist53[i] * np.exp((custlist53[i] - next_cust53) / custlist53[i])
    sigma_c55 = demand_55 / custlist55[i] * np.exp((custlist55[i] - next_cust55) / custlist55[i])
    sigma_c22 = demand_22 / custlist22[i] * np.exp((custlist22[i] - next_cust22) / custlist22[i])
    print(np.exp((custlist33[i]-next_cust33)/custlist33[i]))
    valList33.append(sigma_c33)
    valList53.append(sigma_c53)
    valList55.append(sigma_c55)
    valList22.append(sigma_c22)

    custlist33.append(next_cust33)
    custlist53.append(next_cust53)
    custlist55.append(next_cust55)
    custlist22.append(next_cust22)

custlist33.pop()
custlist53.pop()
custlist55.pop()
custlist22.pop()

plt.subplot(1, 3, 1)
plt.plot(timestep, valList33, '-or', label='$\sigma_c$ at (2%$\u2191$,-1%$\u2193$)')
plt.plot(timestep, valList53, '-pg', label='$\sigma_c$ at (4%$\u2191$,-3%$\u2193$)')
plt.plot(timestep, valList55, '->k', label='$\sigma_c$ at (7%$\u2191$,-6%$\u2193$)')
plt.plot(timestep, valList22, '-vb', label='$\sigma_c$ at (12%$\u2191$, -8%$\u2193$)')
plt.xlabel('Number of Time Steps\n(a)')
plt.ylabel(ylabel='$\sigma_c$')
plt.xlim(-1,25)
plt.legend()
plt.grid(True)

ipv6in=300
ipv4in=900
npall=16
np4=npall
traffic25=[]
for i in timestep:
    ipv6in+=ipv6in*0.03     #ipv6 traffic increament by 2%
    ipv4in-=ipv4in*0.005     #ipv4 traffic increment by 5%
    traf_status= (npall-np4)/npall*ipv6in/(ipv4in+ipv6in)
    np4-=npall/24
    traffic25.append(traf_status)

plt.subplot(1, 3, 2)
plt.plot(timestep, traffic25, '-pg', label='$\sigma_p$ at (3%$\u2191$,-0.5%$\u2193$)')

ipv6in=300
ipv4in=900
npall=16
np4=npall
traffic55=[]
for i in timestep:
    ipv6in+=ipv6in*0.04     #ipv6 traffic increament by 2%
    ipv4in-=ipv4in*0.02     #ipv4 traffic increment by 0.5%%
    traf_status= (npall-np4)/npall*ipv6in/(ipv4in+ipv6in)
    np4-=npall/24
    traffic55.append(traf_status)

plt.plot(timestep, traffic55, '-or', label='$\sigma_p$ at (4%$\u2191$,-2%$\u2193$)')

ipv6in=300
ipv4in=900
npall=16
np4=npall
traffic121=[]
for i in timestep:
    ipv6in+=ipv6in*0.08     #ipv6 traffic increament by 2%
    ipv4in-=ipv4in*0.04     #ipv4 traffic increment by 0.8%%
    traf_status= (npall-np4)/npall*ipv6in/(ipv4in+ipv6in)
    np4-=npall/24
    traffic121.append(traf_status)

plt.plot(timestep, traffic121, '-vb', label='$\sigma_p$ at (8%$\u2191$,-4%$\u2193$)')
plt.xlim(-1,25)
plt.xlabel('Number of Time Steps\n(b)')
plt.legend()
plt.grid(True)


ipv6in=300
ipv4in=900
npall=16
np4=npall
traffic12=[]
for i in timestep:
    ipv6in+=ipv6in*0.10     #ipv6 traffic increament by 2%
    ipv4in-=ipv4in*0.06     #ipv4 traffic increment by 0.8%%
    traf_status= (npall-np4)/npall*ipv6in/(ipv4in+ipv6in)
    np4-=npall/24
    traffic12.append(traf_status)

plt.plot(timestep, traffic12, '->k', label='$\sigma_p$ at (8%$\u2191$,-6%$\u2193$)')
plt.xlim(-1,25)
plt.xlabel('Number of Time Steps\n(b)')
plt.ylabel(ylabel='$\sigma_p$')
plt.legend()
plt.grid(True)

hrall=120
hrs6=2
bt=30
cm=45

hrval22=[]
for hr6 in timestep:
    bt+=bt*0.02
    cm+=cm*0.02
    hrs6+=hrs6/24
    valhr=hr6*bt/(hrall*cm)
    hrval22.append(valhr)

plt.subplot(1, 3, 3)
plt.plot(timestep, hrval22, '-pg', label='$\sigma_s$ at(2%$\u2191$,2%$\u2191$)')

hrs6=2
bt=30
cm=45

hrval221=[]
for hr6 in timestep:
    bt-=bt*0.01
    cm+=cm*0.04
    hrs6+=hrs6/24
    valhr=hr6*bt/(hrall*cm)
    hrval221.append(valhr)

plt.subplot(1, 3, 3)
plt.plot(timestep, hrval221, '-or', label='$\sigma_s$ at(-1%$\u2193$,4%$\u2191$)')


hrs6=2
bt=30
cm=45
hrval52=[]
for hr6 in timestep:
    bt+=bt*0.015
    cm+=cm*0.05
    hrs6+=hrs6/24
    valhr=hr6*bt/(hrall*cm)
    hrval52.append(valhr)
plt.plot(timestep, hrval52, '-vb', label='$\sigma_s$ at (1.5%$\u2191$,5%$\u2191$)')


hrs6=2
bt=30
cm=45

hrval521=[]
for hr6 in timestep:
    bt+=bt*0.03
    cm+=cm*0.07
    hrs6+=hrs6/24
    valhr=hr6*bt/(hrall*cm)
    hrval521.append(valhr)

# plt.subplot(1, 3, 3)
# plt.plot(timestep, hrval521, '->k', label='$\sigma_s$ at(3%$\u2191$,7%$\u2191$)')
# plt.xlabel('Number of Time Steps\n(c)')
# plt.ylabel(ylabel='$\sigma_s$')
# plt.xlim(-1,25)
# plt.legend()
# plt.grid(True)
# plt.show()

sigma32=[]
sigma53=[]
sigma33=[]
sigma55=[]

for i in range(24):
    sigma32.append(valList22[i]+traffic25[i]+hrval22[i])
    sigma53.append(valList53[i]+traffic55[i]+hrval52[i])
    sigma33.append(valList33[i]+traffic121[i]+hrval221[i])
    sigma55.append(valList55[i]+traffic12[i]+hrval521[i])

# plt.subplot(1,2,1)
# plt.plot(timestep, sigma32, '-ob',
#          label='$\sigma$ at $\sigma_c$(12%$\u2191$,-8%$\u2193$), $\sigma_p$(3%$\u2191$,-0.5%$\u2193$) & $\sigma_s$(2%$\u2191$,2%$\u2191$)')
# plt.plot(timestep, sigma53, '-pg',
#          label='$\sigma$ at $\sigma_c$(4%$\u2191$,-3%$\u2193$),$\sigma_p$(4%$\u2191$,-2%$\u2193$) & $\sigma_s$(3%$\u2191$,7%$\u2191$)')
# plt.xlabel('Number of Time Steps\n(a)')
# plt.ylabel(ylabel='$\sigma$')
# plt.xlim(-1,25)
# plt.legend()
# plt.grid(True)

# plt.subplot(1,2,2)
# plt.plot(timestep, sigma33, '->k',
#          label='$\sigma$ at $\sigma_c$(2%$\u2191$,-1%$\u2193$), $\sigma_p$(8%$\u2191$,-4%$\u2193$) & $\sigma_s$(-1%$\u2193$,4%$\u2191$)')
# plt.plot(timestep, sigma55, '-vb',
#          label='$\sigma$ at $\sigma_c$(7%$\u2191$,-6%$\u2193$),$\sigma_p$(10%$\u2191$,-6%$\u2193$) & $\sigma_s$(3%$\u2191$,7%$\u2191$)')
# plt.xlabel('Number of Time Steps\n(b)')
# plt.ylabel(ylabel='$\sigma$')
# plt.xlim(-1,25)
# plt.legend()
# plt.grid(True)

# plt.show()

# graphs of ISP utilities simulation of evolutionary dynamics
def v4_utility(x46, N1):
    return np.log(1 + (N1 - x46) * 500)  # k is the corelation coefficient between SDN and IPv6

def v6_utility(x46, N2):
    return np.log(1 + (N2 + x46) * 700)


# N = 16
# N1 = 12
# N2 = N - N1
# x46 = np.arange(0, N1 + 0.0001, 1)  # cost sharing factor between SDN and IPv6
# plt.subplot(2, 2, 1)
# plt.plot(x46, v4_utility(x46, N1), '-or', label='Group-1(12 legacy IPv4 ISPs)')
# plt.plot(x46, v6_utility(x46, N2), '-pg', label='Group-2(4 SoDIP6 ISPs)')
# plt.xlabel('(a) X4->6 (Number of ISPs transitioning to SoDIP6 networks)')
# plt.ylabel('U$_k$')
# plt.legend()
# plt.grid(True)

# N1 = 8
# N2 = N - N1
# x46 = np.arange(0, N1 + 0.0001, 1)
# plt.subplot(2, 2, 2)
# plt.plot(x46, v4_utility(x46, N1), '-or', label='Group-1(8 Legacy IPv4 ISPs)')
# plt.plot(x46, v6_utility(x46, N2), '-pg', label='Group-2(8 SoDIP6 ISPs)')
# plt.xlabel('(b) X4->6 (Number of ISPs transitioning to SoDIP6 networks)')
# plt.ylabel('U$_k$')
# plt.legend()
# plt.grid(True)

# N1 = 4
# N2 = N - N1
# x46 = np.arange(0, N1 + 0.0001, 1)
# plt.subplot(2, 2, 3)
# plt.plot(x46, v4_utility(x46, N1), '-or', label='Group-1(4 Legacy IPv4 ISPs)')
# plt.plot(x46, v6_utility(x46, N2), '-pg', label='Group-2(12 SoDIP6 ISPs)')
# plt.xlabel('(c) X4->6 (Number of ISPs transitioning to SoDIP6 networks)')
# plt.ylabel('U$_k$')
# plt.legend()
# plt.grid(True)

# N1 = 0
# N2 = N - N1
# x46 = np.arange(0, N1 + 0.0001, 1)
# plt.subplot(2, 2, 4)
# plt.plot(x46, v4_utility(x46, N1), '-or', label='Group-1(0 Legacy IPv4 ISPs)')
# plt.plot(x46, v6_utility(x46, N2), '-pg', label='Group-2(16 SoDIP6 ISPs)')
# plt.xlabel('(d) X4->6 (Number of ISPs transitioning to SoDIP6 networks)')
# plt.ylabel('U$_k$')
# plt.legend()
# plt.grid(True)

# plt.show()
