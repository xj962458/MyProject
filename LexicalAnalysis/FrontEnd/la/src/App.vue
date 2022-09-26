<template>
  <link rel="icon" href="<%= BASE_URL %>favicon.ico" />
  <LexicalAnalysis />
</template>

<script lang="ts">
import { defineComponent } from "vue";
import LexicalAnalysis from "./components/LexicalAnalysis.vue";

export default defineComponent({
  name: "App",
  components: {
    LexicalAnalysis,
  },
});
</script>

<style>
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
  margin-top: 60px;
}
</style>
