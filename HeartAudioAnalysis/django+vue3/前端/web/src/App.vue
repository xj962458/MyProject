<template>
  <nav>
    <!-- <router-link to="/">Home</router-link> | -->
    <router-link to="/">波形图</router-link>|
    <router-link to="/figure2">频谱图</router-link>|
    <router-link to="/figure3">梅尔语谱图</router-link>|
    <router-link to="/figure4">响度曲线</router-link>|
    <router-link to="/Xl">心率曲线</router-link>
  </nav>
  <router-view />
</template>



<style>
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
}

nav {
  padding: 20px;
  font-size: large;
}

nav a {
  font-weight: bold;
  color: #2c3e50;
}

nav a.router-link-exact-active {
  color: #42b983;
}
</style>
